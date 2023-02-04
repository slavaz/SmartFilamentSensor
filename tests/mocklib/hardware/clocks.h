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

#ifndef MOCKLIB_HARDWARE_CLOCKS__H
#define MOCKLIB_HARDWARE_CLOCKS__H

#include "pico/stdlib.h"

enum clock_index
{
    clk_gpout0 = 0, ///< GPIO Muxing 0
    clk_gpout1,     ///< GPIO Muxing 1
    clk_gpout2,     ///< GPIO Muxing 2
    clk_gpout3,     ///< GPIO Muxing 3
    clk_ref,        ///< Watchdog and timers reference clock
    clk_sys,        ///< Processors, bus fabric, memory, memory mapped registers
    clk_peri,       ///< Peripheral clock for UART and SPI
    clk_usb,        ///< USB clock
    clk_adc,        ///< ADC clock
    clk_rtc,        ///< Real time clock
    CLK_COUNT
};

uint32_t clock_get_hz(enum clock_index clk_index);

#endif
