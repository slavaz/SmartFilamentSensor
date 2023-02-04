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
static SensorManagement defaultEngineSensor;
static SensorManagement defaultFilamentSensor;
static Timer defaultTimer;

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

event_movement_state_t
EventController::getCurrentMovementState()
{
    event_movement_state_t movementState;

    bool filamentMoved;
    bool engineMoved;

    filamentMoved = this->filamentSensor->moved();
    engineMoved = this->engineSensor->moved();

    movementState = (filamentMoved && !engineMoved) ? EVENT_MOVEMENT_ONLY_FILAMENT : (!filamentMoved && engineMoved) ? EVENT_MOVEMENT_ONLY_ENGINE
                                                                                 : (filamentMoved && engineMoved)    ? EVENT_MOVEMENT_FILAMENT_AND_ENGINE
                                                                                                                     : EVENT_MOVEMENT_STOP;

    return movementState;
}
/* --------------------------------------------------------------------------------------------- */

void EventController::showDecorations()
{
    switch (this->state)
    {
    case EVENT_WAITING_IN_ERROR:
        this->rgbLed->set(&RgbLed::RED);
        break;

    case EVENT_MANUAL_FEED:
        this->rgbLed->set(&RgbLed::YELLOW);
        break;
    case EVENT_RETRACTION:
        this->rgbLed->set(&RgbLed::BLUE);
        break;
    default:
        this->rgbLed->set(&RgbLed::GREEN);
    }
}
/* ----------------------------------s----------------------------------------------------------- */

event_state_t EventController::handleEvent_none(const event_movement_state_t movementState)
{
    if (EVENT_MOVEMENT_STOP == movementState)
    {
        return EVENT_NONE;
    }
    puts("Started EVENT_WAIT_BEFORE_MOVING after EVENT_NONE");
    this->timer->init(WAIT_BEFORE_MOVING_MILLISEC);

    return EVENT_WAIT_BEFORE_MOVING;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handleEvent_waitBeforeMoving(const event_movement_state_t movementState)
{
    if (!this->timer->hasEnded())
    {
        return EVENT_WAIT_BEFORE_MOVING;
    }
    this->filamentSensor->reset();
    this->engineSensor->reset();
    puts("Started EVENT_MOVING after EVENT_WAIT_BEFORE_MOVING");
    return EVENT_MOVING;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handleEvent_moving(const event_movement_state_t movementState)
{

    switch (movementState)
    {
    case EVENT_MOVEMENT_ONLY_ENGINE:
        this->timer->init(ERROR_TOLERANCE_MILLISEC);
        puts("!!! Started EVENT_SUSPECTION_ON_ERROR after EVENT_MOVING(EVENT_MOVEMENT_ONLY_ENGINE)");
        return EVENT_SUSPECTION_ON_ERROR;

    case EVENT_MOVEMENT_ONLY_FILAMENT:
        puts("Started EVENT_MANUAL_FEED after EVENT_MOVING");
        return EVENT_MANUAL_FEED;

    case EVENT_MOVEMENT_FILAMENT_AND_ENGINE:
        if (this->engineSensor->hasFastMovement())
        {
            puts("Started EVENT_RETRACTION after EVENT_MOVING");
            return EVENT_RETRACTION;
        }
        this->filamentSensor->calculateAverageInterval();
        this->engineSensor->calculateAverageInterval();
        return EVENT_MOVING;
    }
    puts("Started EVENT_NONE after EVENT_MOVING");
    return EVENT_NONE;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handleEvent_retraction(const event_movement_state_t movementState)
{
    if (EVENT_MOVEMENT_FILAMENT_AND_ENGINE == movementState)
    {
        if (this->engineSensor->hasFastMovement())
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

event_state_t EventController::handleEvent_manualFeed(const event_movement_state_t movementState)
{
    if (EVENT_MOVEMENT_ONLY_FILAMENT == movementState)
    {
        return EVENT_MANUAL_FEED;
    }
    puts("Started EVENT_NONE after EVENT_MANUAL_FEED");
    return EVENT_NONE;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handleEvent_suspectionOnError(const event_movement_state_t movementState)
{
    if (EVENT_MOVEMENT_ONLY_ENGINE != movementState)
    {
        if (EVENT_MOVEMENT_FILAMENT_AND_ENGINE == movementState)
        {
            if (this->engineSensor->hasFastMovement())
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

    if (this->timer->hasEnded())
    {
        this->alarm->set(true);
        this->timer->init(ERROR_WAIT_MILLISEC);
        puts("!!! OPS !!! Started EVENT_WAITING_IN_ERROR after EVENT_SUSPECTION_ON_ERROR");
        return EVENT_WAITING_IN_ERROR;
    }
    return EVENT_SUSPECTION_ON_ERROR;
}

/* --------------------------------------------------------------------------------------------- */

event_state_t EventController::handleEvent_waitingInError(const event_movement_state_t movementState)
{
    if (!this->timer->hasEnded())
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

EventController::EventController()
{
    this->filamentSensor = &defaultFilamentSensor;
    this->engineSensor = &defaultEngineSensor;
    this->timer = &defaultTimer;
}

/* --------------------------------------------------------------------------------------------- */

EventController::EventController(SensorManagement *filamentSensor, SensorManagement *engineSensor, Timer *timer)
{
    this->filamentSensor = filamentSensor;
    this->engineSensor = engineSensor;
    this->timer = timer;
}

/* --------------------------------------------------------------------------------------------- */

void EventController::init(RgbLed *const rgbLed, PinOutput *const alarm, MovementSensor *const filamentSensor, MovementSensor *const engineSensor)
{
    this->alarm = alarm;
    this->rgbLed = rgbLed;
    this->engineSensor->init(engineSensor);
    this->filamentSensor->init(filamentSensor);
    this->state = EVENT_NONE;

    this->alarm->set(false);
    this->filamentSensor->setReadingDelay(FILAMENT_SENSOR_INITIAL_LATENCY_MILLISEC);
    this->engineSensor->setReadingDelay(ENGINE_SENSOR_INITIAL_LATENCY_MILLISEC);
}

/* --------------------------------------------------------------------------------------------- */

void EventController::heartbeat()
{
    event_movement_state_t movementState;

    this->timer->heartbeat();
    this->engineSensor->heartbeat();
    this->filamentSensor->heartbeat();

    movementState = this->getCurrentMovementState();

    switch (this->state)
    {
    case EVENT_NONE:
        this->state = this->handleEvent_none(movementState);
        break;
    case EVENT_WAIT_BEFORE_MOVING:
        this->state = this->handleEvent_waitBeforeMoving(movementState);
        break;
    case EVENT_MOVING:
        this->state = this->handleEvent_moving(movementState);
        break;
    case EVENT_RETRACTION:
        this->state = this->handleEvent_retraction(movementState);
        break;
    case EVENT_MANUAL_FEED:
        this->state = this->handleEvent_manualFeed(movementState);
        break;
    case EVENT_SUSPECTION_ON_ERROR:
        this->state = this->handleEvent_suspectionOnError(movementState);
        break;
    case EVENT_WAITING_IN_ERROR:
        this->state = this->handleEvent_waitingInError(movementState);
        break;
    default:
        this->state = EVENT_NONE;
    }
    this->showDecorations();
}
/* --------------------------------------------------------------------------------------------- */
