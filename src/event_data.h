/*
This file is part of the SmartFilamentSensor distribution
Copyright (C) 2023 Slava Zanko

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

#ifndef EVENT_DATA__H
#define EVENT_DATA__H

#include "sensor_management.h"
#include "timer.h"
#include "movement_state.h"
#include "alarm_state.h"

/*** typedefs(not structures) and defined constants **********************************************/
/*** enums ***************************************************************************************/

typedef enum
{
    EVENT_NONE,
    EVENT_WAIT_BEFORE_MOVING,
    EVENT_MOVING,
    EVENT_RETRACTION,
    EVENT_MANUAL_FEED,
    EVENT_SUSPECTION_ON_ERROR,
    EVENT_WAITING_IN_ERROR,
} event_type_t;

/*** structures declarations (and typedefs of structures)*****************************************/

typedef struct
{
    SensorManagement *filamentSensor;
    SensorManagement *engineSensor;
    Timer *timer;
    event_type_t state;
    event_movement_state_t movementState;
    alarm_state_t alarmState;
} event_data_t;

/*** global variables defined in .c file *********************************************************/
/*** declarations of public functions ************************************************************/
/*** inline functions ****************************************************************************/

#endif /* EVENT_DATA__H */
