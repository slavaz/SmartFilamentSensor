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
