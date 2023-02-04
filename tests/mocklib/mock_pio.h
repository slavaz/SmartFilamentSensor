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

#ifndef MOCK_PIO__H
#define MOCK_PIO__H

#include "hardware/pio.h"

#include "base_mock.h"

typedef enum
{
    MockPioMethod__pio_get_default_sm_config,
    MockPioMethod__sm_config_set_wrap,
    MockPioMethod__sm_config_set_sideset,
    MockPioMethod__sm_config_set_clkdiv,
    MockPioMethod__pio_add_program,
    MockPioMethod__pio_gpio_init,
    MockPioMethod__pio_sm_set_consecutive_pindirs,
    MockPioMethod__sm_config_set_sideset_pins,
    MockPioMethod__sm_config_set_out_shift,
    MockPioMethod__sm_config_set_fifo_join,
    MockPioMethod__pio_sm_init,
    MockPioMethod__pio_sm_set_enabled,
    MockPioMethod__pio_sm_put_blocking,
} MockPioMethod;

typedef enum
{
    MockPioMethodParameter__sm_config_set_wrap__c,
    MockPioMethodParameter__sm_config_set_wrap__target,
    MockPioMethodParameter__sm_config_set_wrap__wrap,
    MockPioMethodParameter__sm_config_set_sideset__c,
    MockPioMethodParameter__sm_config_set_sideset__bit_count,
    MockPioMethodParameter__sm_config_set_sideset__optional,
    MockPioMethodParameter__sm_config_set_sideset__pindirs,
    MockPioMethodParameter__sm_config_set_clkdiv__c,
    MockPioMethodParameter__sm_config_set_clkdiv__div,
    MockPioMethodParameter__pio_add_program__pio,
    MockPioMethodParameter__pio_add_program__program,
    MockPioMethodParameter__pio_gpio_init__pio,
    MockPioMethodParameter__pio_gpio_init__pin,
    MockPioMethodParameter__pio_sm_set_consecutive_pindirs__pio,
    MockPioMethodParameter__pio_sm_set_consecutive_pindirs__sm,
    MockPioMethodParameter__pio_sm_set_consecutive_pindirs__pin_base,
    MockPioMethodParameter__pio_sm_set_consecutive_pindirs__pin_count,
    MockPioMethodParameter__pio_sm_set_consecutive_pindirs__is_out,
    MockPioMethodParameter__sm_config_set_sideset_pins__c,
    MockPioMethodParameter__sm_config_set_sideset_pins__sideset_base,
    MockPioMethodParameter__sm_config_set_out_shift__c,
    MockPioMethodParameter__sm_config_set_out_shift__shift_right,
    MockPioMethodParameter__sm_config_set_out_shift__autopull,
    MockPioMethodParameter__sm_config_set_out_shift__pull_threshold,
    MockPioMethodParameter__sm_config_set_fifo_join__c,
    MockPioMethodParameter__sm_config_set_fifo_join__join,
    MockPioMethodParameter__pio_sm_init__pio,
    MockPioMethodParameter__pio_sm_init__sm,
    MockPioMethodParameter__pio_sm_init__initial_pc,
    MockPioMethodParameter__pio_sm_init__config,
    MockPioMethodParameter__pio_sm_set_enabled__pio,
    MockPioMethodParameter__pio_sm_set_enabled__sm,
    MockPioMethodParameter__pio_sm_set_enabled__enabled,
    MockPioMethodParameter__pio_sm_put_blocking__pio,
    MockPioMethodParameter__pio_sm_put_blocking__sm,
    MockPioMethodParameter__pio_sm_put_blocking__data,
} MockPioMethodParameter;

class MockPio : public BaseMock<MockPioMethod, MockPioMethodParameter>
{
private:
public:
};

extern MockPio mockPio;
extern pio_sm_config mock_pio_config;

#endif
