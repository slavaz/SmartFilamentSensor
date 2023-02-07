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

#include "events_handler.h"

#include "event/event_handler_none.h"
#include "event/event_handler_waitbeforemoving.h"
#include "event/event_handler_moving.h"
#include "event/event_handler_retraction.h"
#include "event/event_handler_manualfeed.h"
#include "event/event_handler_suspectiononerror.h"
#include "event/event_handler_waitinginerror.h"

/*** file scope macro definitions ****************************************************************/

#define ERROR_TOLERANCE_MILLISEC 500
#define ERROR_WAIT_MILLISEC 4000
#define WAIT_BEFORE_MOVING_MILLISEC 300

/*** file scope type declarations ****************************************************************/
EventsHandler::handlers_t EventsHandler::defaultHandlers = {
    {EVENT_NONE, &EventHandlerNone::defaultObject},
    {EVENT_WAIT_BEFORE_MOVING, &EventHandlerWaitBeforeMoving::defaultObject},
    {EVENT_MOVING, &EventHandlerMoving::defaultObject},
    {EVENT_RETRACTION, &EventHandlerRetraction::defaultObject},
    {EVENT_MANUAL_FEED, &EventHandlerManualFeed::defaultObject},
    {EVENT_SUSPECTION_ON_ERROR, &EventHandlerSuspectionOnError::defaultObject},
    {EVENT_WAITING_IN_ERROR, &EventHandlerWaitingInError::defaultObject},
};

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */
EventsHandler::EventsHandler()
{
    this->handlers = &defaultHandlers;
}
/* --------------------------------------------------------------------------------------------- */

EventsHandler::EventsHandler(handlers_t *handlers)
{
    this->handlers = handlers;
}

/* --------------------------------------------------------------------------------------------- */

event_type_t EventsHandler::handle(event_data_t *eventData)
{
    eventData->alarmState = ALARM_STATE_NONE;

    return (this->handlers->find(eventData->state) == this->handlers->end())
               ? EVENT_NONE
               : this->handlers->at(eventData->state)->handle(eventData);
}

/* --------------------------------------------------------------------------------------------- */
