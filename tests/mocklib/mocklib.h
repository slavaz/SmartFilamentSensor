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

#ifndef MOCKLIB__H
#define MOCKLIB__H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "pico/time.h"

class PicoSdkInterface
{
public:
    // Clock functions
    virtual uint32_t clock_get_hz(enum clock_index) = 0;

    // time functions
    virtual absolute_time_t get_absolute_time() = 0;
    virtual int64_t absolute_time_diff_us(absolute_time_t, absolute_time_t) = 0;

    // PIO functions
    virtual pio_sm_config pio_get_default_sm_config() = 0;
    virtual void sm_config_set_wrap(pio_sm_config *, uint, uint) = 0;
    virtual void sm_config_set_sideset(pio_sm_config *, uint, bool, bool) = 0;
    virtual void sm_config_set_clkdiv(pio_sm_config *, float) = 0;
    virtual uint pio_add_program(PIO, const pio_program_t *) = 0;
    virtual void pio_gpio_init(PIO, uint) = 0;
    virtual void pio_sm_set_consecutive_pindirs(PIO, uint, uint, uint, bool) = 0;
    virtual void sm_config_set_sideset_pins(pio_sm_config *, uint) = 0;
    virtual void sm_config_set_out_shift(pio_sm_config *, bool, bool, uint) = 0;
    virtual void sm_config_set_fifo_join(pio_sm_config *, enum pio_fifo_join) = 0;
    virtual void pio_sm_init(PIO, uint, uint, pio_sm_config *) = 0;
    virtual void pio_sm_set_enabled(PIO, uint, bool) = 0;
    virtual void pio_sm_put_blocking(PIO, uint, uint32_t) = 0;

    // gpio functions
    virtual void gpio_init(uint) = 0;
    virtual bool gpio_get(uint) = 0;
    virtual void gpio_set_dir(uint, bool) = 0;
    virtual void gpio_pull_down(uint) = 0;
    virtual void gpio_set_slew_rate(uint, enum gpio_slew_rate) = 0;
    virtual void gpio_put(uint, bool) = 0;
};

class MockPicoSdk : public PicoSdkInterface
{
public:
    MOCK_METHOD(uint32_t, clock_get_hz, (enum clock_index), (override));

    MOCK_METHOD(absolute_time_t, get_absolute_time, (), (override));
    MOCK_METHOD(int64_t, absolute_time_diff_us, (absolute_time_t, absolute_time_t), (override));

    MOCK_METHOD(pio_sm_config, pio_get_default_sm_config, (), (override));
    MOCK_METHOD(void, sm_config_set_wrap, (pio_sm_config *, uint, uint), (override));
    MOCK_METHOD(void, sm_config_set_sideset, (pio_sm_config *, uint, bool, bool), (override));
    MOCK_METHOD(void, sm_config_set_clkdiv, (pio_sm_config *, float), (override));
    MOCK_METHOD(uint, pio_add_program, (PIO, const pio_program_t *), (override));
    MOCK_METHOD(void, pio_gpio_init, (PIO, uint), (override));
    MOCK_METHOD(void, pio_sm_set_consecutive_pindirs, (PIO, uint, uint, uint, bool), (override));
    MOCK_METHOD(void, sm_config_set_sideset_pins, (pio_sm_config *, uint), (override));
    MOCK_METHOD(void, sm_config_set_out_shift, (pio_sm_config *, bool, bool, uint), (override));
    MOCK_METHOD(void, sm_config_set_fifo_join, (pio_sm_config *, enum pio_fifo_join), (override));
    MOCK_METHOD(void, pio_sm_init, (PIO, uint, uint, pio_sm_config *), (override));
    MOCK_METHOD(void, pio_sm_set_enabled, (PIO, uint, bool), (override));
    MOCK_METHOD(void, pio_sm_put_blocking, (PIO, uint, uint32_t), (override));

    MOCK_METHOD(void, gpio_init, (uint), (override));
    MOCK_METHOD(bool, gpio_get, (uint), (override));
    MOCK_METHOD(void, gpio_set_dir, (uint, bool), (override));
    MOCK_METHOD(void, gpio_pull_down, (uint), (override));
    MOCK_METHOD(void, gpio_set_slew_rate, (uint, enum gpio_slew_rate), (override));
    MOCK_METHOD(void, gpio_put, (uint, bool), (override));
};

class MockPicoSdkApi
{
public:
    MockPicoSdk *mockPicoSdk;
};

extern MockPicoSdkApi mockPicoSdkApi;

#endif /* MOCKLIB__H */
