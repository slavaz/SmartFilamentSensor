/*
This file is part of the SmartFilamentSensor distribution
Copyright (C) 2022,2023 Slava Zanko

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

#include "pin_output.h"
#include "rgb_led.h"
#include "events_handler.h"
#include "movement_state.h"

/*** typedefs(not structures) and defined constants **********************************************/

/*** enums ***************************************************************************************/

/*** structures declarations (and typedefs of structures)*****************************************/

class EventController
{
private:
    RgbLed *rgbLed;
    PinOutput *alarm;
    EventsHandler *eventsHandler;

private:
    event_movement_state_t getCurrentMovementState();
    void showDecorations();
    void handleAlarm();

protected:
    event_data_t eventData;

public:
    EventController();
    EventController(SensorManagement *, SensorManagement *, Timer *, EventsHandler *);

    void init(RgbLed *const, PinOutput *const, MovementSensor *const, MovementSensor *const);
    void heartbeat();
};

/*** global variables defined in .c file *********************************************************/

/*** declarations of public functions ************************************************************/

/*** inline functions ****************************************************************************/

#endif /* EVENT_CONTROLLER__H */
