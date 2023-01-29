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

#include "timer.h"

/*** file scope macro definitions ****************************************************************/

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void Timer::init(const uint timeToWaitMilisec)
{
    this->timeToWaitMilisec = timeToWaitMilisec;
    this->startTime = get_absolute_time();
}

/* --------------------------------------------------------------------------------------------- */

void Timer::heartbeat()
{
    this->currentTime = get_absolute_time();
}

/* --------------------------------------------------------------------------------------------- */

bool Timer::hasEnded()
{
    uint differenceMillisec;

    differenceMillisec = absolute_time_diff_us(this->startTime, this->currentTime) / 1000;

    return differenceMillisec > this->timeToWaitMilisec;
}

/* --------------------------------------------------------------------------------------------- */
