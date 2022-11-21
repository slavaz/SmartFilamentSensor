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

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void MovementSensor::init(const uint gpio)
{
    this->pin = gpio;
    this->old_value = 0;

    gpio_init(this->pin);
    gpio_set_dir(this->pin, GPIO_IN);
}

/* --------------------------------------------------------------------------------------------- */

bool MovementSensor::has_movement()
{
    bool current_value;

    current_value = gpio_get(this->pin);
    if (this->old_value != current_value)
    {
        this->old_value = current_value;
        return 1;
    }

    return 0;
}

/* --------------------------------------------------------------------------------------------- */
