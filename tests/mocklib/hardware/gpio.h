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

#ifndef MOCKLIB_HARDWARE_GPIO__H
#define MOCKLIB_HARDWARE_GPIO__H

#include "pico/stdlib.h"

#define GPIO_OUT 1
#define GPIO_IN 0

enum gpio_slew_rate
{
    GPIO_SLEW_RATE_SLOW = 0, ///< Slew rate limiting enabled
    GPIO_SLEW_RATE_FAST = 1  ///< Slew rate limiting disabled
};

void gpio_init(uint);

bool gpio_get(uint);

void gpio_set_dir(uint, bool);

void gpio_pull_down(uint);

void gpio_set_slew_rate(uint, enum gpio_slew_rate);

void gpio_put(uint, bool);

#endif
