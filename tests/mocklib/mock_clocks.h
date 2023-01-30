#ifndef MOCK_CLOCKS__H
#define MOCK_CLOCKS__H

#include "base_mock.h"

typedef enum
{
    MockClocksMethod__clock_get_hz,
} MockClocksMethod;

typedef enum
{
    MockClocksMethodParameter__clock_get_hz__clk_index,
} MockClocksMethodParameter;

class MockClocks : public BaseMock<MockClocksMethod, MockClocksMethodParameter>
{
private:
public:
};

extern MockClocks mockClocks;

#endif
