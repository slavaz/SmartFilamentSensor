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

#include "pico/stdlib.h"

#include "pin_output.h"
#include "event_controller.h"
#include "movement_sensor.h"
#include "rgb_led.h"

/*** file scope macro definitions ****************************************************************/

#define SENSOR_FILAMENT_PIN 2
#define SENSOR_ENGINE_PIN 3
#define ALARM_PIN 5
#define RGB_LED_PIN 16

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

static MovementSensor filamentSensor;
static MovementSensor engineSensor;
static RgbLed rgbLed;
static PinOutput alarm;

static EventController eventController;

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

static void setup()
{
    stdio_init_all();

    rgbLed.init(pio0, RGB_LED_PIN);
    rgbLed.set(&RgbLed::BLUE);

    filamentSensor.init(SENSOR_FILAMENT_PIN);
    engineSensor.init(SENSOR_ENGINE_PIN);

    alarm.init(ALARM_PIN);

    eventController.init(&rgbLed, &alarm, &filamentSensor, &engineSensor);
}

/* --------------------------------------------------------------------------------------------- */

static void loop()
{
    eventController.heartbeat();
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
