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

#ifndef MOVEMENT_SENSOR_H
#define MOVEMENT_SENSOR_H

/*** typedefs(not structures) and defined constants **********************************************/

/*** enums ***************************************************************************************/

/*** structures declarations (and typedefs of structures)*****************************************/

typedef struct
{
    uint pin;
    uint32_t reading_delay; // milliseconds
    bool old_value;
    absolute_time_t last_movement_time;
    int64_t difference_millisec;
} movement_sensor_t;

/*** global variables defined in .c file *********************************************************/

/*** declarations of public functions ************************************************************/

void movement_sensor__init(movement_sensor_t *, const uint gpio);

bool movement_sensor__moved(movement_sensor_t *);

int64_t movement_sensor__get_difference_millisec(const  movement_sensor_t *const);

void movement_sensor__set_reading_delay(movement_sensor_t *const, const uint32_t);

/*** inline functions ****************************************************************************/

#endif /* MOVEMENT_SENSOR_H */
