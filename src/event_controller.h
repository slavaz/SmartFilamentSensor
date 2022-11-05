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

#ifndef EVENT_CONTROLLER__H
#define EVENT_CONTROLLER__H

#include "alarm_output.h"
#include "movement_sensor.h"
#include "rgb_led.h"

/*** typedefs(not structures) and defined constants **********************************************/

/*** enums ***************************************************************************************/

typedef enum
{
    EVENT_NONE,
    EVENT_ONLY_FILAMENT,
    EVENT_ONLY_ENGINE,
    EVENT_FILAMENT_AND_ENGINE,
    EVENT_RETRACTION,
} event_state_t;

/*** structures declarations (and typedefs of structures)*****************************************/

class EventController
{
private:
    RgbLed *rgb_led;
    AlarmOutput *alarm;
    MovementSensor *filament_sensor;
    MovementSensor *engine_sensor;

    uint filament_average_interval;
    uint filament_events_count;

    uint engine_average_interval;
    uint engine_events_count;

    event_state_t state;
    uint count_failures;

private:
    event_state_t get_current_state();
    uint calculate_average_interval(const uint, const uint, const uint);
    void set_average_intervals();
    void show_decorations(const event_state_t);
    bool time_to_adjustment();
    static void adjust_sensor_latency(const char *const, MovementSensor *const, cost uint);

public:
    void init(RgbLed *const rgb_led, AlarmOutput *const alarm, MovementSensor *const filament_sensor, MovementSensor *const engine_sensor);
    void heartbeat();
};

/*** global variables defined in .c file *********************************************************/

/*** declarations of public functions ************************************************************/

/*** inline functions ****************************************************************************/

#endif /* EVENT_CONTROLLER__H */
