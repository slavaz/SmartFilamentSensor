/*
This file is part of the SmartFilamentSensor distribution
Copyright (C) 2022,2023 Slava Zanko

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

#include "event_controller.h"

/*** file scope macro definitions ****************************************************************/

#define FILAMENT_SENSOR_INITIAL_LATENCY_MILLISEC 5000
#define ENGINE_SENSOR_INITIAL_LATENCY_MILLISEC 1000

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/
static SensorManagement defaultEngineSensor;
static SensorManagement defaultFilamentSensor;
static Timer defaultTimer;
static EventsHandler defaultEventHandler;

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

event_movement_state_t
EventController::getCurrentMovementState()
{
    event_movement_state_t movementState;

    bool filamentMoved;
    bool engineMoved;

    filamentMoved = this->eventData.filamentSensor->moved();
    engineMoved = this->eventData.engineSensor->moved();

    movementState = (filamentMoved && !engineMoved)
                        ? EVENT_MOVEMENT_ONLY_FILAMENT
                    : (!filamentMoved && engineMoved)
                        ? EVENT_MOVEMENT_ONLY_ENGINE
                    : (filamentMoved && engineMoved)
                        ? EVENT_MOVEMENT_FILAMENT_AND_ENGINE
                        : EVENT_MOVEMENT_STOP;

    return movementState;
}
/* --------------------------------------------------------------------------------------------- */

void EventController::showDecorations()
{
    switch (this->eventData.state)
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
/* --------------------------------------------------------------------------------------------- */

void EventController::handleAlarm()
{
    switch (this->eventData.alarmState)
    {
    case ALARM_STATE_ON:
        this->alarm->set(true);
        break;
    case ALARM_STATE_OFF:
        this->alarm->set(false);
        break;
    }
}

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

EventController::EventController()
{
    this->eventData.filamentSensor = &defaultFilamentSensor;
    this->eventData.engineSensor = &defaultEngineSensor;
    this->eventData.timer = &defaultTimer;
    this->eventsHandler = &defaultEventHandler;
}

/* --------------------------------------------------------------------------------------------- */

EventController::EventController(SensorManagement *filamentSensor, SensorManagement *engineSensor, Timer *timer, EventsHandler *eventsHandler)
{
    this->eventData.filamentSensor = filamentSensor;
    this->eventData.engineSensor = engineSensor;
    this->eventData.timer = timer;
    this->eventsHandler = eventsHandler;
}

/* --------------------------------------------------------------------------------------------- */

void EventController::init(RgbLed *const rgbLed, PinOutput *const alarm, MovementSensor *const filamentSensor, MovementSensor *const engineSensor)
{
    this->alarm = alarm;
    this->rgbLed = rgbLed;
    this->eventData.engineSensor->init(engineSensor);
    this->eventData.filamentSensor->init(filamentSensor);
    this->eventData.state = EVENT_NONE;

    this->alarm->set(false);
    this->eventData.filamentSensor->setReadingDelay(FILAMENT_SENSOR_INITIAL_LATENCY_MILLISEC);
    this->eventData.engineSensor->setReadingDelay(ENGINE_SENSOR_INITIAL_LATENCY_MILLISEC);
}

/* --------------------------------------------------------------------------------------------- */

void EventController::heartbeat()
{
    this->eventData.timer->heartbeat();
    this->eventData.engineSensor->heartbeat();
    this->eventData.filamentSensor->heartbeat();

    this->eventData.movementState = this->getCurrentMovementState();
    this->eventData.state = this->eventsHandler->handle(&this->eventData);

    this->handleAlarm();
    this->showDecorations();
}
/* --------------------------------------------------------------------------------------------- */
