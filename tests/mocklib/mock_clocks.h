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

#ifndef MOCK_CLOCKS__H
#define MOCK_CLOCKS__H

#include "base_mock.h"

typedef enum
{
    MockClocksMethod__clock_get_hz,
} MockClocksMethod;

typedef enum
{
    MockClocksMethodParameter__clock_get_hz__clk_index,
} MockClocksMethodParameter;

class MockClocks : public BaseMock<MockClocksMethod, MockClocksMethodParameter>
{
private:
public:
};

extern MockClocks mockClocks;

#endif
