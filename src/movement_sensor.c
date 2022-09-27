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

#include <pico/time.h>
#include <hardware/gpio.h>

#include "movement_sensor.h"

/*** file scope macro definitions ****************************************************************/

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

static bool movement_sensor__has_delayed_movement(const movement_sensor_t *movement_sensor)
{
    absolute_time_t current_time;
    int64_t difference_millisec;

    current_time = get_absolute_time();
    difference_millisec = absolute_time_diff_us(movement_sensor->last_movement_time, current_time) / 1000;

    return difference_millisec < movement_sensor->reading_delay;
}

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void movement_sensor__init(movement_sensor_t *movement_sensor, const uint gpio, const uint32_t reading_delay)
{
    movement_sensor->pin = gpio;
    movement_sensor->reading_delay = reading_delay;
    movement_sensor->old_value = 0;
    movement_sensor->last_movement_time = get_absolute_time();
    gpio_init(movement_sensor->pin);
    gpio_set_dir(movement_sensor->pin, GPIO_IN);
}

/* --------------------------------------------------------------------------------------------- */

bool movement_sensor__moved(movement_sensor_t *movement_sensor)
{
    bool current_value;

    current_value = gpio_get(movement_sensor->pin);
    if (movement_sensor->old_value != current_value)
    {
        movement_sensor->old_value = current_value;
        movement_sensor->last_movement_time = get_absolute_time();
        return 1;
    }

    if (movement_sensor__has_delayed_movement(movement_sensor))
    {
        return 1;
    }
    return 0;
}

/* --------------------------------------------------------------------------------------------- */
