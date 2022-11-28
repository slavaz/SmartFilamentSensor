/*
This file is part of the SmartFilamentSensor distribution
Copyright (C) 2022 Slava Zanko

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>

#include "event_controller.h"

/*** file scope macro definitions ****************************************************************/

#define FILAMENT_SENSOR_INITIAL_LATENCY_MILLISEC 5000
#define ENGINE_SENSOR_INITIAL_LATENCY_MILLISEC 1000
#define ERROR_TOLERANCE_MILLISEC 500
#define ERROR_WAIT_MILLISEC 4000
#define WAIT_BEFORE_MOVING_MILLISEC 300

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

event_movement_state_t EventController::get_current_movement_state()
{
    event_movement_state_t movement_state;

    bool filament_moved;
    bool engine_moved;

    filament_moved = this->filament_sensor.moved();
    engine_moved = this->engine_sensor.moved();

    movement_state = (filament_moved && !engine_moved) ? EVENT_MOVEMENT_ONLY_FILAMENT : (!filament_moved && engine_moved) ? EVENT_MOVEMENT_ONLY_ENGINE
                                                                                    : (filament_moved && engine_moved)    ? EVENT_MOVEMENT_FILAMENT_AND_ENGINE
                                                                                                                          : EVENT_MOVEMENT_STOP;

    return movement_state;
}
/* --------------------------------------------------------------------------------------------- */

void EventController::show_decorations()
{
    switch (this->state)
    {
    case EVENT_WAITING_IN_ERROR:
        this->rgb_led->set(&RgbLed::RED);
        break;

    case EVENT_MANUAL_FEED:
        this->rgb_led->set(&RgbLed::YELLOW);
        break;
    case EVENT_RETRACTION:
        this->rgb_led->set(&RgbLed::BLUE);
        break;
    default:
        this->rgb_led->set(&RgbLed::GREEN);
    }
}
/* ----------------------------------s----------------------------------------------------------- */

event_state_t EventController::handle_event_none(const event_movement_state_t movement_state)
{
    if (EVENT_MOVEMENT_STOP == movement_state)
    {
        return EVENT_NONE;
    }
    puts("Started EVENT_WAIT_BEFORE_MOVING after EVENT_NONE");
    this->timer.init(WAIT_BEFORE_MOVING_MILLISEC);

    return EVENT_WAIT_BEFORE_MOVING;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handle_event_wait_before_moving(const event_movement_state_t movement_state)
{
    if (!this->timer.has_ended())
    {
        return EVENT_WAIT_BEFORE_MOVING;
    }
    this->filament_sensor.reset();
    this->engine_sensor.reset();
    puts("Started EVENT_MOVING after EVENT_WAIT_BEFORE_MOVING");
    return EVENT_MOVING;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handle_event_moving(const event_movement_state_t movement_state)
{

    switch (movement_state)
    {
    case EVENT_MOVEMENT_ONLY_ENGINE:
        this->timer.init(ERROR_TOLERANCE_MILLISEC);
        puts("!!! Started EVENT_SUSPECTION_ON_ERROR after EVENT_MOVING(EVENT_MOVEMENT_ONLY_ENGINE)");
        return EVENT_SUSPECTION_ON_ERROR;

    case EVENT_MOVEMENT_ONLY_FILAMENT:
        puts("Started EVENT_MANUAL_FEED after EVENT_MOVING");
        return EVENT_MANUAL_FEED;

    case EVENT_MOVEMENT_FILAMENT_AND_ENGINE:
        if (this->engine_sensor.has_fast_movement())
        {
            puts("Started EVENT_RETRACTION after EVENT_MOVING");
            return EVENT_RETRACTION;
        }
        this->filament_sensor.calculate_average_interval();
        this->engine_sensor.calculate_average_interval();
        return EVENT_MOVING;
    }
    puts("Started EVENT_NONE after EVENT_MOVING");
    return EVENT_NONE;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handle_event_retraction(const event_movement_state_t movement_state)
{
    if (EVENT_MOVEMENT_FILAMENT_AND_ENGINE == movement_state)
    {
        if (this->engine_sensor.has_fast_movement())
        {
            return EVENT_RETRACTION;
        }
        puts("Started EVENT_MOVING after EVENT_RETRACTION");
        return EVENT_MOVING;
    }
    puts("Started EVENT_NONE after EVENT_RETRACTION");
    return EVENT_NONE;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handle_event_manual_feed(const event_movement_state_t movement_state)
{
    if (EVENT_MOVEMENT_ONLY_FILAMENT == movement_state)
    {
        return EVENT_MANUAL_FEED;
    }
    puts("Started EVENT_NONE after EVENT_MANUAL_FEED");
    return EVENT_NONE;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handle_event_suspection_on_error(const event_movement_state_t movement_state)
{
    if (EVENT_MOVEMENT_ONLY_ENGINE != movement_state)
    {
        if (EVENT_MOVEMENT_FILAMENT_AND_ENGINE == movement_state)
        {
            if (this->engine_sensor.has_fast_movement())
            {
                puts("Started EVENT_RETRACTION after EVENT_SUSPECTION_ON_ERROR");
                return EVENT_RETRACTION;
            }
            puts("Started EVENT_MOVING after EVENT_SUSPECTION_ON_ERROR");
            return EVENT_MOVING;
        }
        puts("Started EVENT_NONE after EVENT_SUSPECTION_ON_ERROR");
        return EVENT_NONE;
    }

    if (this->timer.has_ended())
    {
        this->alarm->set(true);
        this->timer.init(ERROR_WAIT_MILLISEC);
        puts("!!! OPS !!! Started EVENT_WAITING_IN_ERROR after EVENT_SUSPECTION_ON_ERROR");
        return EVENT_WAITING_IN_ERROR;
    }
    return EVENT_SUSPECTION_ON_ERROR;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handle_event_waiting_in_error(const event_movement_state_t movement_state)
{
    if (!this->timer.has_ended())
    {
        return EVENT_WAITING_IN_ERROR;
    }

    this->alarm->set(false);
    puts("Started EVENT_NONE after EVENT_WAITING_IN_ERROR");

    return EVENT_NONE;
}

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void EventController::init(RgbLed *const rgb_led, PinOutput *const alarm, MovementSensor *const filament_sensor, MovementSensor *const engine_sensor)
{
    this->alarm = alarm;
    this->rgb_led = rgb_led;
    this->engine_sensor.init(engine_sensor);
    this->filament_sensor.init(filament_sensor);
    this->state = EVENT_NONE;

    this->alarm->set(false);
    this->filament_sensor.set_reading_delay(FILAMENT_SENSOR_INITIAL_LATENCY_MILLISEC);
    this->engine_sensor.set_reading_delay(ENGINE_SENSOR_INITIAL_LATENCY_MILLISEC);
}

/* --------------------------------------------------------------------------------------------- */

void EventController::heartbeat()
{
    event_movement_state_t movement_state;

    this->timer.heartbeat();
    this->engine_sensor.heartbeat();
    this->filament_sensor.heartbeat();

    movement_state = this->get_current_movement_state();

    switch (this->state)
    {
    case EVENT_NONE:
        this->state = this->handle_event_none(movement_state);
        break;
    case EVENT_WAIT_BEFORE_MOVING:
        this->state = this->handle_event_wait_before_moving(movement_state);
        break;
    case EVENT_MOVING:
        this->state = this->handle_event_moving(movement_state);
        break;
    case EVENT_RETRACTION:
        this->state = this->handle_event_retraction(movement_state);
        break;
    case EVENT_MANUAL_FEED:
        this->state = this->handle_event_manual_feed(movement_state);
        break;
    case EVENT_SUSPECTION_ON_ERROR:
        this->state = this->handle_event_suspection_on_error(movement_state);
        break;
    case EVENT_WAITING_IN_ERROR:
        this->state = this->handle_event_waiting_in_error(movement_state);
        break;
    default:
        this->state = EVENT_NONE;
    }
    this->show_decorations();
}
/* --------------------------------------------------------------------------------------------- */
