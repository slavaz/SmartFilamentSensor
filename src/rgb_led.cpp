/*
This file is part of the SmartFilamentSensor distribution
Copyright (C) 2022 Slava Zanko

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

/*
    RGB led control for RP2040-Zero https://www.waveshare.com/wiki/RP2040-Zero
    Looks like the RGB led is WS2812 https://datasheetspdf.com/datasheet/WS2812.html
*/

#include "hardware/clocks.h"

#include "rgb_led.h"

/*** file scope macro definitions ****************************************************************/

#define RGB_LED__PIO_SM 0
#define RGB_LED__PIO_SHIFT 32
#define RGB_LED__PIO_FREQ 800000
#define RGB_LED__WRAP_TARGET 0
#define RGB_LED__WRAP 3
#define RGB_LED__CYCLES 10

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

// some googled magic here
static const uint16_t rgbLedInstructions[] = {0x6221, 0x1123, 0x1400, 0xa442};

static const struct pio_program rgbLedProgram = {
    .instructions = rgbLedInstructions,
    .length = 4,
    .origin = -1,
};

/*** global variables ****************************************************************************/

const rgb_t RgbLed::RED = {
    .red = 255,
    .green = 0,
    .blue = 0,
};

const rgb_t RgbLed::GREEN = {
    .red = 0,
    .green = 255,
    .blue = 0,
};

const rgb_t RgbLed::BLUE = {
    .red = 0,
    .green = 0,
    .blue = 255,
};

const rgb_t RgbLed::YELLOW = {
    .red = 255,
    .green = 255,
    .blue = 0,
};

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

pio_sm_config RgbLed::lowlevel_getConfig(const uint offset)
{
    pio_sm_config config;

    config = pio_get_default_sm_config();
    sm_config_set_wrap(&config, offset + RGB_LED__WRAP_TARGET, offset + RGB_LED__WRAP);
    sm_config_set_sideset(&config, 1, false, false);

    return config;
}

/* --------------------------------------------------------------------------------------------- */

void RgbLed::lowlevel_setClockdiv(pio_sm_config *const config)
{
    float clockdiv;

    clockdiv = clock_get_hz(clk_sys) / (RGB_LED__PIO_FREQ * RGB_LED__CYCLES);

    sm_config_set_clkdiv(config, clockdiv);
}

/* --------------------------------------------------------------------------------------------- */

void RgbLed::lowlevel_init(const PIO pio, const uint pin)
{
    pio_sm_config config;

    uint offset = pio_add_program(pio, &rgbLedProgram);

    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, RGB_LED__PIO_SM, pin, 1, true);

    config = RgbLed::lowlevel_getConfig(offset);
    sm_config_set_sideset_pins(&config, pin);
    sm_config_set_out_shift(&config, false, true, RGB_LED__PIO_SHIFT);
    sm_config_set_fifo_join(&config, PIO_FIFO_JOIN_TX);

    RgbLed::lowlevel_setClockdiv(&config);

    pio_sm_init(pio, RGB_LED__PIO_SM, offset, &config);
    pio_sm_set_enabled(pio, RGB_LED__PIO_SM, true);
}

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void RgbLed::init(const pio_hw_t *pio, const uint pin)
{
    this->pio = (pio_hw_t *)pio;

    RgbLed::lowlevel_init(this->pio, pin);
}

/* --------------------------------------------------------------------------------------------- */

void RgbLed::set(const rgb_t *rgb)
{
    uint32_t pixelGrb;

    pixelGrb = (rgb->red << 16) | (rgb->green << 8) | (rgb->blue << 0);

    pio_sm_put_blocking(this->pio, RGB_LED__PIO_SM, pixelGrb << 8u);
}

/* --------------------------------------------------------------------------------------------- */
