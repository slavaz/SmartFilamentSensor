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

#include "mocklib.h"

pio_sm_config pio_get_default_sm_config()
{
    return mockPicoSdkApi.mockPicoSdk->pio_get_default_sm_config();
}

void sm_config_set_wrap(pio_sm_config *c, uint wrap_target, uint wrap)
{
    mockPicoSdkApi.mockPicoSdk->sm_config_set_wrap(c, wrap_target, wrap);
}

void sm_config_set_sideset(pio_sm_config *c, uint bit_count, bool optional, bool pindirs)
{
    mockPicoSdkApi.mockPicoSdk->sm_config_set_sideset(c, bit_count, optional, pindirs);
}

void sm_config_set_clkdiv(pio_sm_config *c, float div)
{
    mockPicoSdkApi.mockPicoSdk->sm_config_set_clkdiv(c, div);
}

uint pio_add_program(PIO pio, const pio_program_t *program)
{
    return mockPicoSdkApi.mockPicoSdk->pio_add_program(pio, program);
}

void pio_gpio_init(PIO pio, uint pin)
{
    mockPicoSdkApi.mockPicoSdk->pio_gpio_init(pio, pin);
}

void pio_sm_set_consecutive_pindirs(PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out)
{
    mockPicoSdkApi.mockPicoSdk->pio_sm_set_consecutive_pindirs(pio, sm, pin_base, pin_count, is_out);
}

void sm_config_set_sideset_pins(pio_sm_config *c, uint sideset_base)
{
    mockPicoSdkApi.mockPicoSdk->sm_config_set_sideset_pins(c, sideset_base);
}

void sm_config_set_out_shift(pio_sm_config *c, bool shift_right, bool autopull, uint pull_threshold)
{
    mockPicoSdkApi.mockPicoSdk->sm_config_set_out_shift(c, shift_right, autopull, pull_threshold);
}

void sm_config_set_fifo_join(pio_sm_config *c, enum pio_fifo_join join)
{
    mockPicoSdkApi.mockPicoSdk->sm_config_set_fifo_join(c, join);
}

void pio_sm_init(PIO pio, uint sm, uint initial_pc, pio_sm_config *config)
{
    mockPicoSdkApi.mockPicoSdk->pio_sm_init(pio, sm, initial_pc, config);
}

void pio_sm_set_enabled(PIO pio, uint sm, bool enabled)
{
    mockPicoSdkApi.mockPicoSdk->pio_sm_set_enabled(pio, sm, enabled);
}

void pio_sm_put_blocking(PIO pio, uint sm, uint32_t data)
{
    mockPicoSdkApi.mockPicoSdk->pio_sm_put_blocking(pio, sm, data);
}
