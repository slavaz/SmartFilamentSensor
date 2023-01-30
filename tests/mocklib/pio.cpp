
#include "mock_pio.h"

MockPio mockPio;

pio_sm_config mock_pio_config;

pio_sm_config pio_get_default_sm_config()
{
    mockPio.methodWasCalled(MockPioMethod__pio_get_default_sm_config);

    return mock_pio_config;
}

void sm_config_set_wrap(pio_sm_config *c, uint wrap_target, uint wrap)
{
    mockPio.methodWasCalled(MockPioMethod__sm_config_set_wrap);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_wrap__c, (uintptr_t)c);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_wrap__target, wrap_target);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_wrap__wrap, wrap);
}

void sm_config_set_sideset(pio_sm_config *c, uint bit_count, bool optional, bool pindirs)
{
    mockPio.methodWasCalled(MockPioMethod__sm_config_set_sideset);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_sideset__c, (uintptr_t)c);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_sideset__bit_count, bit_count);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_sideset__optional, optional);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_sideset__pindirs, pindirs);
}

void sm_config_set_clkdiv(pio_sm_config *c, float div)
{
    mockPio.methodWasCalled(MockPioMethod__sm_config_set_clkdiv);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_clkdiv__c, (intptr_t)c);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_clkdiv__div, div);
}

uint pio_add_program(PIO pio, const pio_program_t *program)
{
    mockPio.methodWasCalled(MockPioMethod__pio_add_program);
    mockPio.setParameter(MockPioMethodParameter__pio_add_program__pio, (intptr_t)pio);
    mockPio.setParameter(MockPioMethodParameter__pio_add_program__program, (intptr_t)program);

    return mockPio.getMethodReturnValue(MockPioMethod__pio_add_program);
}

void pio_gpio_init(PIO pio, uint pin)
{
    mockPio.methodWasCalled(MockPioMethod__pio_gpio_init);
    mockPio.setParameter(MockPioMethodParameter__pio_gpio_init__pio, (intptr_t)pio);
    mockPio.setParameter(MockPioMethodParameter__pio_gpio_init__pin, pin);
}

void pio_sm_set_consecutive_pindirs(PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out)
{
    mockPio.methodWasCalled(MockPioMethod__pio_sm_set_consecutive_pindirs);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_set_consecutive_pindirs__pio, (intptr_t)pio);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_set_consecutive_pindirs__sm, sm);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_set_consecutive_pindirs__pin_base, pin_base);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_set_consecutive_pindirs__pin_count, pin_count);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_set_consecutive_pindirs__is_out, is_out);
}

void sm_config_set_sideset_pins(pio_sm_config *c, uint sideset_base)
{
    mockPio.methodWasCalled(MockPioMethod__sm_config_set_sideset_pins);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_sideset_pins__c, (intptr_t)c);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_sideset_pins__sideset_base, sideset_base);
}

void sm_config_set_out_shift(pio_sm_config *c, bool shift_right, bool autopull, uint pull_threshold)
{
    mockPio.methodWasCalled(MockPioMethod__sm_config_set_out_shift);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_out_shift__c, (intptr_t)c);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_out_shift__shift_right, shift_right);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_out_shift__autopull, autopull);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_out_shift__pull_threshold, pull_threshold);
}

void sm_config_set_fifo_join(pio_sm_config *c, enum pio_fifo_join join)
{
    mockPio.methodWasCalled(MockPioMethod__sm_config_set_fifo_join);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_fifo_join__c, (intptr_t)c);
    mockPio.setParameter(MockPioMethodParameter__sm_config_set_fifo_join__join, join);
}

void pio_sm_init(PIO pio, uint sm, uint initial_pc, const pio_sm_config *config)
{
    mockPio.methodWasCalled(MockPioMethod__pio_sm_init);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_init__pio, (intptr_t)pio);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_init__sm, sm);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_init__initial_pc, initial_pc);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_init__config, (intptr_t)config);
}

void pio_sm_set_enabled(PIO pio, uint sm, bool enabled)
{
    mockPio.methodWasCalled(MockPioMethod__pio_sm_set_enabled);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_set_enabled__pio, (intptr_t)pio);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_set_enabled__sm, sm);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_set_enabled__enabled, enabled);
}

void pio_sm_put_blocking(PIO pio, uint sm, uint32_t data)
{
    mockPio.methodWasCalled(MockPioMethod__pio_sm_put_blocking);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_put_blocking__pio, (intptr_t)pio);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_put_blocking__sm, sm);
    mockPio.setParameter(MockPioMethodParameter__pio_sm_put_blocking__data, data);
}
