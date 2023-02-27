/*
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
#include "mocklib.h"
#include "movement_sensor.h"

using ::testing::Return;

#define TEST_PIN_NUMBER 123

TEST(MovementSensor, hasMovement)
{
  MockPicoSdk mockPicoSdk;
  mockPicoSdkApi.mockPicoSdk = &mockPicoSdk;

  MovementSensor sensor;

  EXPECT_CALL(mockPicoSdk, gpio_init(TEST_PIN_NUMBER));
  EXPECT_CALL(mockPicoSdk, gpio_set_dir(TEST_PIN_NUMBER, 0));
  EXPECT_CALL(mockPicoSdk, gpio_pull_down(TEST_PIN_NUMBER));

  sensor.init(TEST_PIN_NUMBER);

  EXPECT_CALL(mockPicoSdk, gpio_get(TEST_PIN_NUMBER)).Times(2).WillOnce(Return(false)).WillOnce(Return(true));

  EXPECT_EQ(false, sensor.hasMovement());
  EXPECT_EQ(true, sensor.hasMovement());
}
