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

#ifndef MOCKLIB_HARDWARE_PIO__H
#define MOCKLIB_HARDWARE_PIO__H

#include "pico/stdlib.h"

typedef struct pio_program
{
    const uint16_t *instructions;
    uint8_t length;
    int8_t origin;
} pio_program_t;

typedef struct
{

} pio_hw_t;

typedef struct
{
    uint32_t clkdiv;
    uint32_t execctrl;
    uint32_t shiftctrl;
    uint32_t pinctrl;
} pio_sm_config;

typedef pio_hw_t *PIO;

enum pio_fifo_join
{
    PIO_FIFO_JOIN_NONE = 0,
    PIO_FIFO_JOIN_TX = 1,
    PIO_FIFO_JOIN_RX = 2,
};

pio_sm_config pio_get_default_sm_config(void);

void sm_config_set_wrap(pio_sm_config *c, uint wrap_target, uint wrap);

void sm_config_set_sideset(pio_sm_config *c, uint bit_count, bool optional, bool pindirs);

void sm_config_set_clkdiv(pio_sm_config *c, float div);

uint pio_add_program(PIO pio, const pio_program_t *program);

void pio_gpio_init(PIO pio, uint pin);

void pio_sm_set_consecutive_pindirs(PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out);

void sm_config_set_sideset_pins(pio_sm_config *c, uint sideset_base);

void sm_config_set_out_shift(pio_sm_config *c, bool shift_right, bool autopull, uint pull_threshold);

void sm_config_set_fifo_join(pio_sm_config *c, enum pio_fifo_join join);

void pio_sm_init(PIO pio, uint sm, uint initial_pc, pio_sm_config *config);

void pio_sm_set_enabled(PIO pio, uint sm, bool enabled);

void pio_sm_put_blocking(PIO pio, uint sm, uint32_t data);

#endif
