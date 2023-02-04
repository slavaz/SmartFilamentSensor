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
#include "movement_sensor.h"

#define TEST_PIN_NUMBER 123

TEST(MovementSensor, init)
{
  MovementSensor sensor;

  mockGpio.reset();

  sensor.init(TEST_PIN_NUMBER);

  EXPECT_EQ(1, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_init));
  EXPECT_EQ(TEST_PIN_NUMBER, mockGpio.getParameter(MockGpioMethodParameter__gpio_init__gpio));

  EXPECT_EQ(1, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_set_dir));
  EXPECT_EQ(TEST_PIN_NUMBER, mockGpio.getParameter(MockGpioMethodParameter__gpio_set_dir__gpio));
  EXPECT_EQ(0, mockGpio.getParameter(MockGpioMethodParameter__gpio_set_dir__out));

  EXPECT_EQ(1, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_pull_down));
}

TEST(MovementSensor, hasMovement)
{
  MovementSensor sensor;
  mockGpio.reset();

  sensor.init(TEST_PIN_NUMBER);

  mockGpio.setMethodReturnValue(MockGpioMethod__gpio_get, 0);
  EXPECT_EQ(0, sensor.hasMovement());
  EXPECT_EQ(0, sensor.hasMovement());
  EXPECT_EQ(2, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_get));

  mockGpio.setMethodReturnValue(MockGpioMethod__gpio_get, 1);
  EXPECT_EQ(1, sensor.hasMovement());
  EXPECT_EQ(0, sensor.hasMovement());
  EXPECT_EQ(4, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_get));

  mockGpio.setMethodReturnValue(MockGpioMethod__gpio_get, 0);
  EXPECT_EQ(1, sensor.hasMovement());
  EXPECT_EQ(0, sensor.hasMovement());
  EXPECT_EQ(6, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_get));

  EXPECT_EQ(0, sensor.hasMovement());
  EXPECT_EQ(7, mockGpio.getCountMethodCalls(MockGpioMethod__gpio_get));
}
