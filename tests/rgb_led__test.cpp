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
#include "mock_pio.h"
#include "mock_clocks.h"
#include "rgb_led.h"
#include "hardware/clocks.h"

#define TEST_PIN_NUMBER 123
#define TEST_PIO 456
#define TEST_OFFSET 789

TEST(RgbLed, init__pio_add_program)
{
    RgbLed rgbLed;

    mockPio.reset();

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__pio_add_program));

    EXPECT_EQ(TEST_PIO, mockPio.getParameter(MockPioMethodParameter__pio_add_program__pio));

    const struct pio_program *fetched_arg_program =
        (struct pio_program *)mockPio.getParameter(MockPioMethodParameter__pio_add_program__program);

    EXPECT_EQ(4, fetched_arg_program->length);
    EXPECT_EQ(-1, fetched_arg_program->origin);
    EXPECT_EQ(0x6221, fetched_arg_program->instructions[0]);
    EXPECT_EQ(0x1123, fetched_arg_program->instructions[1]);
    EXPECT_EQ(0x1400, fetched_arg_program->instructions[2]);
    EXPECT_EQ(0xa442, fetched_arg_program->instructions[3]);
}

TEST(RgbLed, init__pio_gpio_init)
{
    RgbLed rgbLed;

    mockPio.reset();

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__pio_gpio_init));
    EXPECT_EQ(TEST_PIN_NUMBER, mockPio.getParameter(MockPioMethodParameter__pio_gpio_init__pin));
    EXPECT_EQ(TEST_PIO, mockPio.getParameter(MockPioMethodParameter__pio_gpio_init__pio));
}

TEST(RgbLed, init__pio_sm_set_consecutive_pindirs)
{
    RgbLed rgbLed;

    mockPio.reset();

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__pio_sm_set_consecutive_pindirs));
    EXPECT_EQ(TEST_PIO, mockPio.getParameter(MockPioMethodParameter__pio_sm_set_consecutive_pindirs__pio));
    EXPECT_EQ(0, mockPio.getParameter(MockPioMethodParameter__pio_sm_set_consecutive_pindirs__sm));
    EXPECT_EQ(TEST_PIN_NUMBER, mockPio.getParameter(MockPioMethodParameter__pio_sm_set_consecutive_pindirs__pin_base));
    EXPECT_EQ(1, mockPio.getParameter(MockPioMethodParameter__pio_sm_set_consecutive_pindirs__pin_count));
    EXPECT_EQ(true, mockPio.getParameter(MockPioMethodParameter__pio_sm_set_consecutive_pindirs__is_out));
}

TEST(RgbLed, init__lowlevel_getConfig)
{
    RgbLed rgbLed;

    mockPio.reset();
    mockPio.setMethodReturnValue(MockPioMethod__pio_add_program, TEST_OFFSET);

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__pio_get_default_sm_config));
    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__sm_config_set_wrap));
    EXPECT_EQ(TEST_OFFSET, mockPio.getParameter(MockPioMethodParameter__sm_config_set_wrap__target));
    EXPECT_EQ(TEST_OFFSET + 3, mockPio.getParameter(MockPioMethodParameter__sm_config_set_wrap__wrap));

    uintptr_t config = mockPio.getParameter(MockPioMethodParameter__sm_config_set_wrap__c);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__sm_config_set_sideset));
    EXPECT_EQ(config, mockPio.getParameter(MockPioMethodParameter__sm_config_set_sideset__c));
    EXPECT_EQ(1, mockPio.getParameter(MockPioMethodParameter__sm_config_set_sideset__bit_count));
    EXPECT_EQ(false, mockPio.getParameter(MockPioMethodParameter__sm_config_set_sideset__optional));
    EXPECT_EQ(false, mockPio.getParameter(MockPioMethodParameter__sm_config_set_sideset__pindirs));
}

TEST(RgbLed, init__sm_config_set_sideset_pins)
{
    RgbLed rgbLed;

    mockPio.reset();
    mockPio.setMethodReturnValue(MockPioMethod__pio_add_program, TEST_OFFSET);

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__sm_config_set_sideset_pins));
    EXPECT_EQ(TEST_PIN_NUMBER, mockPio.getParameter(MockPioMethodParameter__sm_config_set_sideset_pins__sideset_base));
}

TEST(RgbLed, init__sm_config_set_out_shift)
{
    RgbLed rgbLed;

    mockPio.reset();
    mockPio.setMethodReturnValue(MockPioMethod__pio_add_program, TEST_OFFSET);

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);

    uintptr_t config = mockPio.getParameter(MockPioMethodParameter__sm_config_set_sideset_pins__c);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__sm_config_set_out_shift));
    EXPECT_EQ(config, mockPio.getParameter(MockPioMethodParameter__sm_config_set_out_shift__c));
    EXPECT_EQ(false, mockPio.getParameter(MockPioMethodParameter__sm_config_set_out_shift__shift_right));
    EXPECT_EQ(true, mockPio.getParameter(MockPioMethodParameter__sm_config_set_out_shift__autopull));
    EXPECT_EQ(32, mockPio.getParameter(MockPioMethodParameter__sm_config_set_out_shift__pull_threshold));
}

TEST(RgbLed, init__sm_config_set_fifo_join)
{
    RgbLed rgbLed;

    mockPio.reset();
    mockPio.setMethodReturnValue(MockPioMethod__pio_add_program, TEST_OFFSET);

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);

    uintptr_t config = mockPio.getParameter(MockPioMethodParameter__sm_config_set_sideset_pins__c);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__sm_config_set_fifo_join));
    EXPECT_EQ(config, mockPio.getParameter(MockPioMethodParameter__sm_config_set_fifo_join__c));
    EXPECT_EQ(PIO_FIFO_JOIN_TX, mockPio.getParameter(MockPioMethodParameter__sm_config_set_fifo_join__join));
}

TEST(RgbLed, init__lowlevel_setClockdiv)
{
    RgbLed rgbLed;

    mockPio.reset();
    mockClocks.reset();

    mockPio.setMethodReturnValue(MockPioMethod__pio_add_program, TEST_OFFSET);
    mockClocks.setMethodReturnValue(MockClocksMethod__clock_get_hz, 24000000);

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);

    uintptr_t config = mockPio.getParameter(MockPioMethodParameter__sm_config_set_sideset_pins__c);

    EXPECT_EQ(1, mockClocks.getCountMethodCalls(MockClocksMethod__clock_get_hz));
    EXPECT_EQ(clk_sys, mockClocks.getParameter(MockClocksMethodParameter__clock_get_hz__clk_index));

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__sm_config_set_clkdiv));
    EXPECT_EQ(config, mockPio.getParameter(MockPioMethodParameter__sm_config_set_clkdiv__c));
    EXPECT_EQ(3, mockPio.getParameter(MockPioMethodParameter__sm_config_set_clkdiv__div));
}

TEST(RgbLed, init__pio_sm_init)
{
    RgbLed rgbLed;

    mockPio.reset();
    mockPio.setMethodReturnValue(MockPioMethod__pio_add_program, TEST_OFFSET);

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);

    uintptr_t config = mockPio.getParameter(MockPioMethodParameter__sm_config_set_sideset_pins__c);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__pio_sm_init));
    EXPECT_EQ(TEST_PIO, mockPio.getParameter(MockPioMethodParameter__pio_sm_init__pio));
    EXPECT_EQ(0, mockPio.getParameter(MockPioMethodParameter__pio_sm_init__sm));
    EXPECT_EQ(TEST_OFFSET, mockPio.getParameter(MockPioMethodParameter__pio_sm_init__initial_pc));
    EXPECT_EQ(config, mockPio.getParameter(MockPioMethodParameter__pio_sm_init__config));
}

TEST(RgbLed, init__pio_sm_set_enabled)
{
    RgbLed rgbLed;

    mockPio.reset();
    mockPio.setMethodReturnValue(MockPioMethod__pio_add_program, TEST_OFFSET);

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__pio_sm_set_enabled));
    EXPECT_EQ(TEST_PIO, mockPio.getParameter(MockPioMethodParameter__pio_sm_set_enabled__pio));
    EXPECT_EQ(0, mockPio.getParameter(MockPioMethodParameter__pio_sm_set_enabled__sm));
    EXPECT_EQ(true, mockPio.getParameter(MockPioMethodParameter__pio_sm_set_enabled__enabled));
}

class RgbLedSetParametersTests : public ::testing::TestWithParam<std::tuple<rgb_t *, uint>>
{
protected:
    RgbLed rgbLed;
};

TEST_P(RgbLedSetParametersTests, setTime)
{
    auto [color, expectedResult] = GetParam();
    uintptr_t actualResult;

    mockPio.reset();

    rgbLed.init((const pio_hw_t *)TEST_PIO, TEST_PIN_NUMBER);
    rgbLed.set(color);

    EXPECT_EQ(1, mockPio.getCountMethodCalls(MockPioMethod__pio_sm_put_blocking));
    EXPECT_EQ(TEST_PIO, mockPio.getParameter(MockPioMethodParameter__pio_sm_put_blocking__pio));
    EXPECT_EQ(0, mockPio.getParameter(MockPioMethodParameter__pio_sm_put_blocking__sm));
    actualResult = mockPio.getParameter(MockPioMethodParameter__pio_sm_put_blocking__data);
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
