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

#include "event_handler_suspectiononerror.h"
#include "constants.h"

/*** file scope macro definitions ****************************************************************/

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

EventHandlerSuspectionOnError EventHandlerSuspectionOnError::defaultObject;

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

event_type_t
EventHandlerSuspectionOnError::handleNormalMovement(event_data_t *eventData)
{
    if (EVENT_MOVEMENT_FILAMENT_AND_ENGINE == eventData->movementState)
    {
        if (eventData->engineSensor->hasFastMovement())
        {
            puts("Started EVENT_RETRACTION after EVENT_SUSPECTION_ON_ERROR");
            return EVENT_RETRACTION;
        }
        puts("Started EVENT_MOVING after EVENT_SUSPECTION_ON_ERROR");
        return EVENT_MOVING;
    }
    puts("Started EVENT_NONE after EVENT_SUSPECTION_ON_ERROR");
    return EVENT_NONE;
}

/* --------------------------------------------------------------------------------------------- */

event_type_t
EventHandlerSuspectionOnError::handleErrorneosMovement(event_data_t *eventData)
{
    if (eventData->timer->hasEnded())
    {
        eventData->alarmState = ALARM_STATE_ON;
        eventData->timer->init(ERROR_WAIT_MILLISEC);
        puts("!!! OPS !!! Started EVENT_WAITING_IN_ERROR after EVENT_SUSPECTION_ON_ERROR");
        return EVENT_WAITING_IN_ERROR;
    }
    return EVENT_SUSPECTION_ON_ERROR;
}

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

event_type_t
EventHandlerSuspectionOnError::handle(event_data_t *eventData)
{
    if (EVENT_MOVEMENT_ONLY_ENGINE != eventData->movementState)
    {
        return this->handleNormalMovement(eventData);
    }

    return this->handleErrorneosMovement(eventData);
}

/* --------------------------------------------------------------------------------------------- */
