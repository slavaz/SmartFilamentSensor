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

#include "event_handler_manualfeed.h"

/*** file scope macro definitions ****************************************************************/

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

EventHandlerManualFeed EventHandlerManualFeed::defaultObject;

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

event_type_t
EventHandlerManualFeed::handle(event_data_t *eventData)
{
    if (EVENT_MOVEMENT_ONLY_FILAMENT == eventData->movementState)
    {
        return EVENT_MANUAL_FEED;
    }
    puts("Started EVENT_NONE after EVENT_MANUAL_FEED");
    return EVENT_NONE;
}

/* --------------------------------------------------------------------------------------------- */
