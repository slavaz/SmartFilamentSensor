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

#define FILAMENT_SENSOR_INITIAL_LATENCY_MILLISEC 3000
#define ENGINE_SENSOR_INITIAL_LATENCY_MILLISEC 1000

#define ADJUSTMENT_TIME_MULTIPLIER 4

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::get_current_state()
{
    event_state_t state;

    bool filament_moved;
    bool engine_moved;

    filament_moved = this->filament_sensor.moved();
    engine_moved = this->engine_sensor.moved();

    state = (filament_moved && !engine_moved) ? EVENT_ONLY_FILAMENT : (!filament_moved && engine_moved) ? EVENT_ONLY_ENGINE
                                                                  : (filament_moved && engine_moved)    ? EVENT_FILAMENT_AND_ENGINE
                                                                                                        : EVENT_NONE;

    if ((EVENT_FILAMENT_AND_ENGINE == this->state || EVENT_RETRACTION == this->state) && EVENT_FILAMENT_AND_ENGINE == state)
    {
        // an attempt to recognize a retraction
        if (this->engine_sensor.has_fast_movement())
        {
            state = EVENT_RETRACTION;
        }
    }

    return state;
}
/* --------------------------------------------------------------------------------------------- */

void EventController::set_average_intervals()
{
    this->filament_sensor.calculate_average_interval();
    this->engine_sensor.calculate_average_interval();
}

/* ----------------------------------s----------------------------------------------------------- */

void EventController::show_decorations(const event_state_t state)
{
    if (state == this->state)
    {
        return;
    }

    switch (state)
    {
    case EVENT_ONLY_ENGINE:
        this->rgb_led->set(&RgbLed::RED);
        puts("[ERROR] Looks like a filament is ended or stucks!");
        break;

    case EVENT_ONLY_FILAMENT:
        this->rgb_led->set(&RgbLed::YELLOW);
        puts("[WARNING] Looks like a filement is manually loaded or unloaded. Isn't it?");
        break;

    case EVENT_RETRACTION:
        this->rgb_led->set(&RgbLed::BLUE);
        puts("[DEBUG] Retraction");
        break;

    default:
        this->rgb_led->set(&RgbLed::GREEN);
    }
}

/* ----------------------------------s----------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void EventController::init(RgbLed *const rgb_led, PinOutput *const alarm, MovementSensor *const filament_sensor, MovementSensor *const engine_sensor)
{
    this->alarm = alarm;
    this->rgb_led = rgb_led;
    this->engine_sensor.init(engine_sensor);
    this->filament_sensor.init(filament_sensor);
    this->state = EVENT_NONE;
    this->count_failures = 0;

    this->filament_sensor.set_reading_delay(FILAMENT_SENSOR_INITIAL_LATENCY_MILLISEC);
    this->engine_sensor.set_reading_delay(ENGINE_SENSOR_INITIAL_LATENCY_MILLISEC);
}

/* --------------------------------------------------------------------------------------------- */

void EventController::heartbeat()
{
    event_state_t current_state;

    this->engine_sensor.heartbeat();
    this->filament_sensor.heartbeat();

    current_state = this->get_current_state();

    this->show_decorations(current_state);

    switch (current_state)
    {
    case EVENT_ONLY_ENGINE:
        if (++this->count_failures >= ADJUSTMENT_TIME_MULTIPLIER - 1)
        {
            this->alarm->set(true);
        }
        break;
    case EVENT_FILAMENT_AND_ENGINE:
        this->set_average_intervals();

    default:
        this->alarm->set(false);
        this->count_failures = 0;
    }

    this->state = current_state;
}
/* --------------------------------------------------------------------------------------------- */