#ifndef MOCK_TIME__H
#define MOCK_TIME__H

#include "base_mock.h"

typedef enum
{
    MockTimeMethod__get_absolute_time,
    MockTimeMethod__absolute_time_diff_us,
} MockTimeMethod;

typedef enum
{
    MockTimeMethodParameter__absolute_time_diff_us__from,
    MockTimeMethodParameter__absolute_time_diff_us__to,
} MockTimeMethodParameter;

class MockTime : public BaseMock<MockTimeMethod, MockTimeMethodParameter>
{
private:
public:
};

extern MockTime mockTime;

#endif
