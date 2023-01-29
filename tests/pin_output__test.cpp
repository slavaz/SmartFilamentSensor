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
    EXPECT_EQ(TEST_PIN_NUMBER, mockGpio.getParameter(MockGpioMethodParameter__gpio_init__gpio));

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
