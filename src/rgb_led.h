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

#ifndef RGB_LED_H
#define RGB_LED_H

#include "hardware/pio.h"

/*** typedefs(not structures) and defined constants **********************************************/

/*** enums ***************************************************************************************/

/*** structures declarations (and typedefs of structures)*****************************************/

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgb_t;

typedef struct
{
    pio_hw_t *pio;
} rgb_led_t;

/*** global variables defined in .c file *********************************************************/

extern const rgb_t RGB_RED;
extern const rgb_t RGB_GREEN;
extern const rgb_t RGB_BLUE;

/*** declarations of public functions ************************************************************/

void rgb_led__init(rgb_led_t *, const pio_hw_t *, const uint);

void rgb_led__set(const rgb_led_t *, const rgb_t *);

/*** inline functions ****************************************************************************/

#endif /* RGB_LED_H */
