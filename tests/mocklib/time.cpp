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

#include "pico/time.h"

#include "mock_time.h"

MockTime mockTime;

absolute_time_t get_absolute_time(void)
{
    mockTime.methodWasCalled(MockTimeMethod__get_absolute_time);

    return mockTime.getMethodReturnValue(MockTimeMethod__get_absolute_time);
}

int64_t absolute_time_diff_us(absolute_time_t from, absolute_time_t to)
{
    mockTime.methodWasCalled(MockTimeMethod__absolute_time_diff_us);
    mockTime.setParameter(MockTimeMethodParameter__absolute_time_diff_us__from, from);
    mockTime.setParameter(MockTimeMethodParameter__absolute_time_diff_us__to, to);

    return (int64_t)(to - from);
}