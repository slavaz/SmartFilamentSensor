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

#include <stdio.h>
#include "pico/stdlib.h"

#include "movement_sensor.h"
#include "rgb_led.h"

/*** file scope macro definitions ****************************************************************/

#define SENSOR_FILAMENT_PIN 2
#define SENSOR_ENGINE_PIN 3
#define ALARM_PIN 5
#define RGB_LED_PIN 16

#define DELAY_SENSOR_READING_MILLISEC 3000

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

static MovementSensor filament_sensor;
static MovementSensor engine_sensor;
static RgbLed rgb_led;

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

static void alarm_init()
{
    gpio_init(ALARM_PIN);
    gpio_set_dir(ALARM_PIN, GPIO_OUT);
}

/* --------------------------------------------------------------------------------------------- */

static void alarm_if(const bool alarm_flag)
{
    gpio_put(ALARM_PIN, alarm_flag);

    rgb_led.set(alarm_flag ? &RgbLed::RED : &RgbLed::GREEN);
}

/* --------------------------------------------------------------------------------------------- */

static void setup()
{
    stdio_init_all();

    rgb_led.init(pio0, RGB_LED_PIN);
    rgb_led.set(&RgbLed::BLUE);

    filament_sensor.init(SENSOR_FILAMENT_PIN);
    filament_sensor.set_reading_delay(DELAY_SENSOR_READING_MILLISEC);

    engine_sensor.init(SENSOR_ENGINE_PIN);
    engine_sensor.set_reading_delay(DELAY_SENSOR_READING_MILLISEC);

    alarm_init();
}

/* --------------------------------------------------------------------------------------------- */

static void loop()
{
    bool filament_moved;
    bool engine_moved;

    filament_moved = filament_sensor.moved();
    engine_moved = engine_sensor.moved();

    printf("Filament: %d, engine: %d, alarm: %d\n", filament_moved, engine_moved, engine_moved && !filament_moved);

    alarm_if(engine_moved && !filament_moved);

    sleep_ms(10);
}

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

int main()
{
    setup();

    while (1)
    {
        loop();
    }

    return 0;
}

/* --------------------------------------------------------------------------------------------- */
