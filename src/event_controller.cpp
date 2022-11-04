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

#include "event_controller.h"

/*** file scope macro definitions ****************************************************************/

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void EventController::init(RgbLed *const rgb_led, AlarmOutput *const alarm, MovementSensor *const filament_sensor, MovementSensor *const engine_sensor)
{
    this->alarm = alarm;
    this->rgb_led = rgb_led;
    this->engine_sensor = engine_sensor;
    this->filament_sensor = filament_sensor;
}

/* --------------------------------------------------------------------------------------------- */

void EventController::heartbeat()
{

    bool filament_moved;
    bool engine_moved;

    filament_moved = this->filament_sensor->moved();
    engine_moved = this->engine_sensor->moved();

    printf("Filament: %d, engine: %d, alarm: %d\n", filament_moved, engine_moved, engine_moved && !filament_moved);

    this->alarm->set(engine_moved && !filament_moved);
    this->rgb_led->set(engine_moved && !filament_moved ? &RgbLed::RED : &RgbLed::GREEN);
}
/* --------------------------------------------------------------------------------------------- */
