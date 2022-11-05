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

#include <hardware/gpio.h>

#include "movement_sensor.h"

/*** file scope macro definitions ****************************************************************/

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

bool MovementSensor::has_delayed_movement()
{
    absolute_time_t current_time;

    current_time = get_absolute_time();
    this->difference_millisec = absolute_time_diff_us(this->last_movement_time, current_time) / 1000;

    return this->difference_millisec < this->reading_delay;
}

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void MovementSensor::init(const uint gpio)
{
    this->pin = gpio;
    this->reading_delay = 0;
    this->difference_millisec = 0;
    this->old_value = 0;
    this->last_movement_time = get_absolute_time();

    gpio_init(this->pin);
    gpio_set_dir(this->pin, GPIO_IN);
}

/* --------------------------------------------------------------------------------------------- */

bool MovementSensor::moved()
{
    bool current_value;

    current_value = gpio_get(this->pin);
    if (this->old_value != current_value)
    {
        this->old_value = current_value;
        this->last_movement_time = get_absolute_time();
        return 1;
    }

    return this->has_delayed_movement();
}

/* --------------------------------------------------------------------------------------------- */

int64_t MovementSensor::get_difference_millisec()
{
    return this->difference_millisec;
}

/* --------------------------------------------------------------------------------------------- */

void MovementSensor::set_reading_delay(const uint32_t reading_delay)
{
    this->reading_delay = reading_delay;
}

/* --------------------------------------------------------------------------------------------- */

uint32_t MovementSensor::get_reading_delay()
{
    return this->reading_delay;
}

/* --------------------------------------------------------------------------------------------- */
