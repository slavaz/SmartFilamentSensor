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

#include "event_handler_waitbeforemoving.h"

/*** file scope macro definitions ****************************************************************/

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

EventHandlerWaitBeforeMoving EventHandlerWaitBeforeMoving::defaultObject;

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

event_type_t
EventHandlerWaitBeforeMoving::handle(event_data_t *eventData)
{
    if (!eventData->timer->hasEnded())
    {
        return EVENT_WAIT_BEFORE_MOVING;
    }
    eventData->filamentSensor->reset();
    eventData->engineSensor->reset();
    puts("Started EVENT_MOVING after EVENT_WAIT_BEFORE_MOVING");
    return EVENT_MOVING;
}

/* --------------------------------------------------------------------------------------------- */
