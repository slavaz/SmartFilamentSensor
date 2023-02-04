
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

#include "hardware/gpio.h"

#include "mock_gpio.h"

MockGpio mockGpio;

void gpio_init(uint gpio)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_init);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_init__gpio, gpio);
}

bool gpio_get(uint gpio)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_get);
    return mockGpio.getMethodReturnValue(MockGpioMethod__gpio_get);
}

void gpio_set_dir(uint gpio, bool out)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_set_dir);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_set_dir__gpio, gpio);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_set_dir__out, out);
}

void gpio_pull_down(uint gpio)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_pull_down);
}

void gpio_set_slew_rate(uint gpio, enum gpio_slew_rate slew)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_set_slew_rate);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_set_slew_rate__gpio, gpio);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_set_slew_rate__slew, slew);
}

void gpio_put(uint gpio, bool value)
{
    mockGpio.methodWasCalled(MockGpioMethod__gpio_put);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_put__gpio, gpio);
    mockGpio.setParameter(MockGpioMethodParameter__gpio_put__value, value);
}
