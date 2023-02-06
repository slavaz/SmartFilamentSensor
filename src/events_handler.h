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

#ifndef EVENTS_HANDLER__H
#define EVENTS_HANDLER__H

#include <map>

#include "event_data.h"
#include "event/event_handler.h"

/*** typedefs(not structures) and defined constants **********************************************/

/*** enums ***************************************************************************************/

/*** structures declarations (and typedefs of structures)*****************************************/

class EventsHandler : public EventHandler
{
public:
    typedef std::map<event_type_t, EventHandler *> handlers_t;

private:
    handlers_t *handlers;

    static handlers_t defaultHandlers;

public:
    EventsHandler();
    EventsHandler(handlers_t *);

    virtual event_type_t handle(event_data_t *);
};

/*** global variables defined in .c file *********************************************************/

/*** declarations of public functions ************************************************************/
/*** inline functions ****************************************************************************/

#endif /* EVENTS_HANDLER__H */
