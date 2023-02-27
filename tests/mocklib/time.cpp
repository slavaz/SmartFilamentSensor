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
#include "mocklib.h"

absolute_time_t get_absolute_time(void)
{
    return mockPicoSdkApi.mockPicoSdk->get_absolute_time();
}

int64_t absolute_time_diff_us(absolute_time_t from, absolute_time_t to)
{
    return mockPicoSdkApi.mockPicoSdk->absolute_time_diff_us(from, to);
}