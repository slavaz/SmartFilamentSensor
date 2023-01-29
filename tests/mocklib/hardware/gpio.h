#ifndef MOCKLIB_HARDWARE_GPIO__H
#define MOCKLIB_HARDWARE_GPIO__H

#include "pico/stdlib.h"

#define GPIO_OUT 1
#define GPIO_IN 0

enum gpio_slew_rate
{
    GPIO_SLEW_RATE_SLOW = 0, ///< Slew rate limiting enabled
    GPIO_SLEW_RATE_FAST = 1  ///< Slew rate limiting disabled
};

void gpio_init(uint);

bool gpio_get(uint);

void gpio_set_dir(uint, bool);

void gpio_pull_down(uint);

void gpio_set_slew_rate(uint, enum gpio_slew_rate);

void gpio_put(uint gpio, bool value);

#endif
