#include "pico/time.h"

#include "mock_time.h"

MockTime mockTime;

absolute_time_t get_absolute_time(void)
{
    mockTime.methodWasCalled(MockTimeMethod__get_absolute_time);

    return mockTime.getMethodReturnValue(MockTimeMethod__get_absolute_time);
}

int64_t absolute_time_diff_us(absolute_time_t from, absolute_time_t to)
{
    mockTime.methodWasCalled(MockTimeMethod__absolute_time_diff_us);
    mockTime.setParameter(MockTimeMethodParameter__absolute_time_diff_us__from, from);
    mockTime.setParameter(MockTimeMethodParameter__absolute_time_diff_us__to, to);

    return (int64_t)(to - from);
}