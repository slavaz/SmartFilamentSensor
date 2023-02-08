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

#ifndef SENSOR_MANAGEMENT__H
#define SENSOR_MANAGEMENT__H

#include <pico/stdlib.h>
#include <pico/time.h>
#include "movement_sensor.h"

/*** typedefs(not structures) and defined constants **********************************************/

/*** enums ***************************************************************************************/

/*** structures declarations (and typedefs of structures)*****************************************/

class SensorManagement
{
protected:
    MovementSensor *sensor;
    bool hasSensorMovement;
    uint32_t readingDelay; // milliseconds
    absolute_time_t lastMovementTime;
    uint differenceMillisec;
    uint previousDifferenceMillisec;
    int64_t totalEventsCount;
    uint averageIntervalBetweenEvents;

protected:
    bool hasDelayedMovement();

public:
    virtual void init(MovementSensor *const);
    virtual void heartbeat();
    virtual void calculateAverageInterval();

    virtual void reset();

    virtual bool moved();

    virtual bool hasFastMovement();

    virtual void setReadingDelay(const uint32_t);
    uint32_t getReadingDelay();
};

/*** global variables defined in .c file *********************************************************/

/*** declarations of public functions ************************************************************/

/*** inline functions ****************************************************************************/

#endif /* SENSOR_MANAGEMENT__H */
