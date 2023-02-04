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

