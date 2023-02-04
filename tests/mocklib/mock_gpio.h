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

#ifndef MOCK_GPIO__H
#define MOCK_GPIO__H

#include "base_mock.h"

typedef enum
{
    MockGpioMethod__gpio_init,
    MockGpioMethod__gpio_get,
    MockGpioMethod__gpio_set_dir,
    MockGpioMethod__gpio_pull_down,
    MockGpioMethod__gpio_set_slew_rate,
    MockGpioMethod__gpio_put,
} MockGpioMethod;

typedef enum
{
    MockGpioMethodParameter__gpio_init__gpio,
    MockGpioMethodParameter__gpio_set_dir__gpio,
    MockGpioMethodParameter__gpio_set_dir__out,
    MockGpioMethodParameter__gpio_set_slew_rate__gpio,
    MockGpioMethodParameter__gpio_set_slew_rate__slew,
    MockGpioMethodParameter__gpio_put__gpio,
    MockGpioMethodParameter__gpio_put__value,
} MockGpioMethodParameter;

class MockGpio : public BaseMock<MockGpioMethod, MockGpioMethodParameter>
{
private:
public:
};

extern MockGpio mockGpio;

#endif
