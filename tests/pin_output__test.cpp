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

#include <gtest/gtest.h>
#include "mock_gpio.h"
#include "pin_output.h"

#define TEST_PIN_NUMBER 123

TEST(PinOutput, init)
{
    PinOutput pinOutput;

    mockGpio.reset();
    pinOutput.init(TEST_PIN_NUMBER);

    EXPECT_EQ(1, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_init));
    EXPECT_EQ(TEST_PIN_NUMBER, (int)mockGpio.getParameter(MockGpioMethodParameter__gpio_init__gpio));

    EXPECT_EQ(1, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_set_dir));
    EXPECT_EQ(TEST_PIN_NUMBER, mockGpio.getParameter(MockGpioMethodParameter__gpio_set_dir__gpio));
    EXPECT_EQ(1, mockGpio.getParameter(MockGpioMethodParameter__gpio_set_dir__out));

    EXPECT_EQ(1, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_pull_down));

    EXPECT_EQ(1, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_set_slew_rate));
    EXPECT_EQ(TEST_PIN_NUMBER, mockGpio.getParameter(MockGpioMethodParameter__gpio_set_slew_rate__gpio));
    EXPECT_EQ(0, mockGpio.getParameter(MockGpioMethodParameter__gpio_set_slew_rate__slew));
}

TEST(PinOutput, set)
{
    PinOutput pinOutput;

    mockGpio.reset();
    pinOutput.init(TEST_PIN_NUMBER);

    pinOutput.set(true);
    EXPECT_EQ(1, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_put));
    EXPECT_EQ(TEST_PIN_NUMBER, mockGpio.getParameter(MockGpioMethodParameter__gpio_put__gpio));
    EXPECT_EQ(true, mockGpio.getParameter(MockGpioMethodParameter__gpio_put__value));

    pinOutput.set(false);
    EXPECT_EQ(2, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_put));
    EXPECT_EQ(TEST_PIN_NUMBER, mockGpio.getParameter(MockGpioMethodParameter__gpio_put__gpio));
    EXPECT_EQ(false, mockGpio.getParameter(MockGpioMethodParameter__gpio_put__value));
}
