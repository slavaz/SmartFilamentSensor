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

#ifndef EVENT_HANDLER__H
#define EVENT_HANDLER__H

#include "../event_data.h"

/*** typedefs(not structures) and defined constants **********************************************/

/*** enums ***************************************************************************************/

/*** structures declarations (and typedefs of structures)*****************************************/

class EventHandler
{
private:
public:
    virtual event_type_t handle(event_data_t *) = 0;
};

/*** global variables defined in .c file *********************************************************/

/*** declarations of public functions ************************************************************/
/*** inline functions ****************************************************************************/

#endif /* EVENT_HANDLER__H */
