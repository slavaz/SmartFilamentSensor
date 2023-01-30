#include "hardware/clocks.h"

#include "mock_clocks.h"

MockClocks mockClocks;

uint32_t
clock_get_hz(enum clock_index clk_index)
{
    mockClocks.methodWasCalled(MockClocksMethod__clock_get_hz);
    mockClocks.setParameter(MockClocksMethodParameter__clock_get_hz__clk_index, clk_index);

    return mockClocks.getMethodReturnValue(MockClocksMethod__clock_get_hz);
}
