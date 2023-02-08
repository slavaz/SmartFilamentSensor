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

#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "event/event_handler.h"

using ::testing::Return;
using ::testing::StrictMock;

MATCHER_P(isArgEqual, expected, std::string(negation ? "is" : "isn't") + " match " + std::to_string(expected))
{
    return (uintptr_t)arg == (uintptr_t)expected;
};

class MockTimer : public Timer
{
public:
    MOCK_METHOD(void, init, (const uint), (override));
    MOCK_METHOD(bool, hasEnded, (), (override));
};

class MockSensorManagement : public SensorManagement
{
public:
    MOCK_METHOD(void, calculateAverageInterval, (), (override));
    MOCK_METHOD(bool, hasFastMovement, (), (override));
    MOCK_METHOD(void, reset, (), (override));
};

template <class T = EventHandler>
class TestCommonHandler
{
protected:
    event_data_t eventData;
    StrictMock<MockTimer> timer;
    StrictMock<MockSensorManagement> filamentSensor, engineSensor;

    T handler;

public:
    TestCommonHandler()
    {
        eventData.timer = &timer;
        eventData.filamentSensor = &filamentSensor;
        eventData.engineSensor = &engineSensor;
    }
};
