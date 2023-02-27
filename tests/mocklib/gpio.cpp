
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

#include "mocklib.h"

void gpio_init(uint gpio)
{
    mockPicoSdkApi.mockPicoSdk->gpio_init(gpio);
}

bool gpio_get(uint gpio)
{
    return mockPicoSdkApi.mockPicoSdk->gpio_get(gpio);
}

void gpio_set_dir(uint gpio, bool out)
{
    mockPicoSdkApi.mockPicoSdk->gpio_set_dir(gpio, out);
}

void gpio_pull_down(uint gpio)
{
    mockPicoSdkApi.mockPicoSdk->gpio_pull_down(gpio);
}

void gpio_set_slew_rate(uint gpio, enum gpio_slew_rate slew)
{

    mockPicoSdkApi.mockPicoSdk->gpio_set_slew_rate(gpio, slew);
}

void gpio_put(uint gpio, bool value)
{
    mockPicoSdkApi.mockPicoSdk->gpio_put(gpio, value);
}
