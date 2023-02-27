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
#include "rgb_led.h"
#include "hardware/clocks.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Eq;
using ::testing::Return;
using ::testing::SaveArg;
using ::testing::SaveArgPointee;

#define TEST_PIN_NUMBER 123
#define TEST_PIO (pio_hw_t *)456
#define TEST_OFFSET 789

MATCHER_P(SameAs, value, ::testing::PrintToString(*value))
{
    return arg == *value;
}

class RgbLedSetParametersTests : public ::testing::TestWithParam<std::tuple<rgb_t *, uint>>
{
protected:
    RgbLed rgbLed;
};

TEST_P(RgbLedSetParametersTests, setColor)
{
    MockPicoSdk mockPicoSdk;
    mockPicoSdkApi.mockPicoSdk = &mockPicoSdk;

    auto [color, expectedResult] = GetParam();
    pio_sm_config config{}, *actualConfig = nullptr;
    const struct pio_program *fetched_arg_program = nullptr;
    PIO pio;
    uintptr_t actualResult;

    EXPECT_CALL(mockPicoSdk, pio_add_program(_, _)).Times(1).WillOnce(DoAll(SaveArg<0>(&pio), SaveArg<1>(&fetched_arg_program), Return(TEST_OFFSET)));

    EXPECT_CALL(mockPicoSdk, pio_gpio_init(Eq(TEST_PIO), Eq(TEST_PIN_NUMBER)));
    EXPECT_CALL(mockPicoSdk, pio_sm_set_consecutive_pindirs(Eq(TEST_PIO), 0, Eq(TEST_PIN_NUMBER), 1, true));
    EXPECT_CALL(mockPicoSdk, pio_get_default_sm_config).WillOnce(Return(config));
    EXPECT_CALL(mockPicoSdk, sm_config_set_wrap(_, Eq(TEST_OFFSET), Eq(TEST_OFFSET + 3))).WillOnce(SaveArg<0>(&actualConfig));
    EXPECT_CALL(mockPicoSdk, sm_config_set_sideset(SameAs(&actualConfig), 1, false, false));
    EXPECT_CALL(mockPicoSdk, sm_config_set_sideset_pins(_, TEST_PIN_NUMBER)).WillOnce(SaveArg<0>(&actualConfig));
    EXPECT_CALL(mockPicoSdk, sm_config_set_out_shift(SameAs(&actualConfig), false, true, 32));
    EXPECT_CALL(mockPicoSdk, sm_config_set_fifo_join(SameAs(&actualConfig), PIO_FIFO_JOIN_TX));
    EXPECT_CALL(mockPicoSdk, clock_get_hz(clk_sys)).WillOnce(Return(24000000));
    EXPECT_CALL(mockPicoSdk, sm_config_set_clkdiv(SameAs(&actualConfig), 3.f));
    EXPECT_CALL(mockPicoSdk, pio_sm_init(TEST_PIO, 0, TEST_OFFSET, SameAs(&actualConfig)));
    EXPECT_CALL(mockPicoSdk, pio_sm_set_enabled(TEST_PIO, 0, true));

    rgbLed.init(TEST_PIO, TEST_PIN_NUMBER);

    EXPECT_EQ(TEST_PIO, pio);
    EXPECT_NE(nullptr, fetched_arg_program);
    EXPECT_EQ(4, fetched_arg_program->length);
    EXPECT_EQ(-1, fetched_arg_program->origin);
    EXPECT_EQ(0x6221, fetched_arg_program->instructions[0]);
    EXPECT_EQ(0x1123, fetched_arg_program->instructions[1]);
    EXPECT_EQ(0x1400, fetched_arg_program->instructions[2]);
    EXPECT_EQ(0xa442, fetched_arg_program->instructions[3]);

    EXPECT_CALL(mockPicoSdk, pio_sm_put_blocking(TEST_PIO, 0, _)).Times(1).WillOnce(SaveArg<2>(&actualResult));

    rgbLed.set(color);

    EXPECT_EQ(expectedResult, actualResult);
}

// color, expectedResult
INSTANTIATE_TEST_CASE_P(
    RgbLed,
    RgbLedSetParametersTests,
    ::testing::Values(
        std::make_tuple((rgb_t *)&RgbLed::BLUE, 0x0000FF00),
        std::make_tuple((rgb_t *)&RgbLed::GREEN, 0x00FF0000),
        std::make_tuple((rgb_t *)&RgbLed::RED, 0xFF000000),
        std::make_tuple((rgb_t *)&RgbLed::YELLOW, 0xFFFF0000)));
