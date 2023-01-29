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

#ifndef RGB_LED__H
#define RGB_LED__H

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

class RgbLed
{
private:
    pio_hw_t *pio;

private:
    static void lowlevel_init(const PIO, const uint);
    static void lowlevel_setClockdiv(pio_sm_config *const);
    static pio_sm_config lowlevel_getConfig(const uint);

public:
    static const rgb_t RED;
    static const rgb_t GREEN;
    static const rgb_t BLUE;
    static const rgb_t YELLOW;

public:
    void init(const pio_hw_t *, const uint);
    void set(const rgb_t *);
};

/*** global variables defined in .c file *********************************************************/

/*** declarations of public functions ************************************************************/
/*** inline functions ****************************************************************************/

#endif /* RGB_LED__H */
