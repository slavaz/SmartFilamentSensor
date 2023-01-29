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

#ifndef EVENT_CONTROLLER__H
#define EVENT_CONTROLLER__H

#include "pin_output.h"
#include "sensor_management.h"
#include "timer.h"
#include "movement_sensor.h"
#include "rgb_led.h"

/*** typedefs(not structures) and defined constants **********************************************/

/*** enums ***************************************************************************************/

typedef enum
{
    EVENT_MOVEMENT_STOP,
    EVENT_MOVEMENT_ONLY_FILAMENT,
    EVENT_MOVEMENT_ONLY_ENGINE,
    EVENT_MOVEMENT_FILAMENT_AND_ENGINE,
} event_movement_state_t;

typedef enum
{
    EVENT_NONE,
    EVENT_WAIT_BEFORE_MOVING,
    EVENT_MOVING,
    EVENT_RETRACTION,
    EVENT_MANUAL_FEED,
    EVENT_SUSPECTION_ON_ERROR,
    EVENT_WAITING_IN_ERROR,
} event_state_t;

/*** structures declarations (and typedefs of structures)*****************************************/

class EventController
{
private:
    RgbLed *rgbLed;
    PinOutput *alarm;
    SensorManagement filamentSensor;
    SensorManagement engineSensor;
    Timer timer;

    event_state_t state;

private:
    event_movement_state_t getCurrentMovementState();
    void showDecorations();

    event_state_t handleEvent_none(const event_movement_state_t);
    event_state_t handleEvent_waitBeforeMoving(const event_movement_state_t);
    event_state_t handleEvent_moving(const event_movement_state_t);
    event_state_t handleEvent_retraction(const event_movement_state_t);
    event_state_t handleEvent_manualFeed(const event_movement_state_t);
    event_state_t handleEvent_suspectionOnError(const event_movement_state_t);
    event_state_t handleEvent_waitingInError(const event_movement_state_t);

public:
    void
    init(RgbLed *const, PinOutput *const, MovementSensor *const, MovementSensor *const);
    void heartbeat();
};

/*** global variables defined in .c file *********************************************************/

/*** declarations of public functions ************************************************************/

/*** inline functions ****************************************************************************/

#endif /* EVENT_CONTROLLER__H */
