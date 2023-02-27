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
#include "pin_output.h"

#define TEST_PIN_NUMBER 123

TEST(PinOutput, set)
{
    MockPicoSdk mockPicoSdk;
    mockPicoSdkApi.mockPicoSdk = &mockPicoSdk;

    PinOutput pinOutput;

    EXPECT_CALL(mockPicoSdk, gpio_init(TEST_PIN_NUMBER));
    EXPECT_CALL(mockPicoSdk, gpio_set_dir(TEST_PIN_NUMBER, 1));
    EXPECT_CALL(mockPicoSdk, gpio_pull_down(TEST_PIN_NUMBER));
    EXPECT_CALL(mockPicoSdk, gpio_set_slew_rate(TEST_PIN_NUMBER, GPIO_SLEW_RATE_SLOW));

    pinOutput.init(TEST_PIN_NUMBER);

    EXPECT_CALL(mockPicoSdk, gpio_put(TEST_PIN_NUMBER, true)).Times(1);
    EXPECT_CALL(mockPicoSdk, gpio_put(TEST_PIN_NUMBER, false)).Times(1);
    pinOutput.set(true);
    pinOutput.set(false);
}
