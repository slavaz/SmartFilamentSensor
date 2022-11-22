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

#include "sensor_management.h"

/*** file scope macro definitions ****************************************************************/

#define FAST_MOVE_MULTIPLIER 5

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

bool SensorManagement::has_delayed_movement()
{
    absolute_time_t current_time;

    current_time = get_absolute_time();
    this->difference_millisec = absolute_time_diff_us(this->last_movement_time, current_time) / 1000;

    return this->difference_millisec < this->reading_delay;
}

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void SensorManagement::init(MovementSensor *const sensor)
{
    this->sensor = sensor;
    this->reading_delay = 0;
    this->total_events_count = 0;
    this->average_interval_between_events = 0;
    this->has_sensor_movement = 0;

    this->reset();
}

/* --------------------------------------------------------------------------------------------- */

void SensorManagement::reset()
{
    this->last_movement_time = get_absolute_time();
    this->previous_difference_millisec = 0;
    this->difference_millisec = 0;
}

/* --------------------------------------------------------------------------------------------- */

void SensorManagement::heartbeat()
{
    this->has_sensor_movement = this->sensor->has_movement();
}

/* --------------------------------------------------------------------------------------------- */

bool SensorManagement::moved()
{

    if (this->has_sensor_movement)
    {
        this->last_movement_time = get_absolute_time();
        this->previous_difference_millisec = this->difference_millisec;
        this->difference_millisec = 0;
        return 1;
    }

    return this->has_delayed_movement();
}

/* --------------------------------------------------------------------------------------------- */
void SensorManagement::calculate_average_interval()
{
    if (this->difference_millisec != 0)
    {
        this->average_interval_between_events = (this->average_interval_between_events * this->total_events_count + this->difference_millisec) /
                                                (this->total_events_count + 1);
        this->total_events_count++;
    }
}

/* --------------------------------------------------------------------------------------------- */

bool SensorManagement::has_fast_movement()
{
    uint fast_movement_limit = this->average_interval_between_events / FAST_MOVE_MULTIPLIER;

    return this->difference_millisec < fast_movement_limit && this->previous_difference_millisec < fast_movement_limit;
}

/* --------------------------------------------------------------------------------------------- */

void SensorManagement::set_reading_delay(const uint32_t reading_delay)
{
    this->reading_delay = reading_delay;
    this->previous_difference_millisec = reading_delay;
}

/* --------------------------------------------------------------------------------------------- */

uint32_t SensorManagement::get_reading_delay()
{
    return this->reading_delay;
}

/* --------------------------------------------------------------------------------------------- */
