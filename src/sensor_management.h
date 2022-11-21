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

#ifndef SENSOR_MANAGEMENT__H
#define SENSOR_MANAGEMENT__H

#include "pico/stdlib.h"
#include <pico/time.h>
#include "movement_sensor.h"

/*** typedefs(not structures) and defined constants **********************************************/

/*** enums ***************************************************************************************/

/*** structures declarations (and typedefs of structures)*****************************************/

class SensorManagement
{
private:
    MovementSensor *sensor;
    bool has_sensor_movement;
    uint32_t reading_delay; // milliseconds
    absolute_time_t last_movement_time;
    uint difference_millisec;
    uint previous_difference_millisec;
    int64_t total_events_count;
    uint average_interval_between_events;

private:
    bool has_delayed_movement();

public:
    void init(MovementSensor *const);
    void heartbeat();
    void calculate_average_interval();

    bool moved();

    bool has_fast_movement();

    void set_reading_delay(const uint32_t);
    uint32_t get_reading_delay();
};

/*** global variables defined in .c file *********************************************************/

/*** declarations of public functions ************************************************************/

/*** inline functions ****************************************************************************/

#endif /* SENSOR_MANAGEMENT__H */
