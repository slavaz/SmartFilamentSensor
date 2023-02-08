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

#include <stdio.h>

#include "event_handler_moving.h"
#include "constants.h"

/*** file scope macro definitions ****************************************************************/

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

EventHandlerMoving EventHandlerMoving::defaultObject;

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

event_type_t
EventHandlerMoving::handle(event_data_t *eventData)
{
    switch (eventData->movementState)
    {
    case EVENT_MOVEMENT_ONLY_ENGINE:
        eventData->timer->init(ERROR_TOLERANCE_MILLISEC);
        puts("!!! Started EVENT_SUSPECTION_ON_ERROR after EVENT_MOVING(EVENT_MOVEMENT_ONLY_ENGINE)");
        return EVENT_SUSPECTION_ON_ERROR;
    case EVENT_MOVEMENT_ONLY_FILAMENT:
        puts("Started EVENT_MANUAL_FEED after EVENT_MOVING");
        return EVENT_MANUAL_FEED;
    case EVENT_MOVEMENT_FILAMENT_AND_ENGINE:
        if (eventData->engineSensor->hasFastMovement())
        {
            puts("Started EVENT_RETRACTION after EVENT_MOVING");
            return EVENT_RETRACTION;
        }
        eventData->filamentSensor->calculateAverageInterval();
        eventData->engineSensor->calculateAverageInterval();
        return EVENT_MOVING;
    }
    puts("Started EVENT_NONE after EVENT_MOVING");
    return EVENT_NONE;
}