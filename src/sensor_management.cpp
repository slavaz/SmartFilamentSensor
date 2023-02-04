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

#include "sensor_management.h"

/*** file scope macro definitions ****************************************************************/

#define FAST_MOVE_MULTIPLIER 5

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** global variables ****************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

bool SensorManagement::hasDelayedMovement()
{
    return this->differenceMillisec < this->readingDelay;
}

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void SensorManagement::init(MovementSensor *const sensor)
{
    this->sensor = sensor;
    this->readingDelay = 0;
    this->totalEventsCount = 0;
    this->averageIntervalBetweenEvents = 0;
    this->hasSensorMovement = 0;

    this->reset();
}

/* --------------------------------------------------------------------------------------------- */

void SensorManagement::reset()
{
    this->lastMovementTime = get_absolute_time();
    this->previousDifferenceMillisec = 0;
    this->differenceMillisec = 0;
}

/* --------------------------------------------------------------------------------------------- */

void SensorManagement::heartbeat()
{
    this->hasSensorMovement = this->sensor->hasMovement();

    this->differenceMillisec = absolute_time_diff_us(this->lastMovementTime, get_absolute_time()) / 1000;
}

/* --------------------------------------------------------------------------------------------- */
bool SensorManagement::moved()
{

    if (this->hasSensorMovement)
    {
        this->lastMovementTime = get_absolute_time();
        this->previousDifferenceMillisec = this->differenceMillisec;
        this->differenceMillisec = 0;
        return true;
    }

    return this->hasDelayedMovement();
}

/* --------------------------------------------------------------------------------------------- */
void SensorManagement::calculateAverageInterval()
{
    if (this->differenceMillisec != 0)
    {
        this->averageIntervalBetweenEvents = (this->averageIntervalBetweenEvents * this->totalEventsCount + this->differenceMillisec) /
                                             (this->totalEventsCount + 1);
        this->totalEventsCount++;
    }
}

/* --------------------------------------------------------------------------------------------- */

bool SensorManagement::hasFastMovement()
{
    uint fastMovementLimit = this->averageIntervalBetweenEvents / FAST_MOVE_MULTIPLIER;

    return this->differenceMillisec < fastMovementLimit && this->previousDifferenceMillisec < fastMovementLimit;
}

/* --------------------------------------------------------------------------------------------- */

void SensorManagement::setReadingDelay(const uint32_t readingDelay)
{
    this->readingDelay = readingDelay;
    this->previousDifferenceMillisec = readingDelay;
}

/* --------------------------------------------------------------------------------------------- */

uint32_t SensorManagement::getReadingDelay()
{
    return this->readingDelay;
}

/* --------------------------------------------------------------------------------------------- */
