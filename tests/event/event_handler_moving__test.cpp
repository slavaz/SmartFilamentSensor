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

#include "event/event_handler_moving.h"

using ::testing::Return;
using ::testing::StrictMock;

class MockTimer : public Timer
{
public:
    MOCK_METHOD(void, init, (const uint), (override));
};

class MockSensorManagement : public SensorManagement
{
public:
    MOCK_METHOD(void, calculateAverageInterval, (), (override));
    MOCK_METHOD(bool, hasFastMovement, (), (override));
};
class EventHandlerMovingTests : public ::testing::TestWithParam<std::tuple<int, int, event_movement_state_t, event_type_t, int, bool, int>>
{
protected:
    event_data_t eventData;
    StrictMock<MockTimer> timer;
    StrictMock<MockSensorManagement> filamentSensor, engineSensor;

    EventHandlerMoving handler;
};

MATCHER_P(isArgEqual, expected, std::string(negation ? "is" : "isn't") + " match " + std::to_string(expected))
{
    return arg == expected;
};

TEST_P(EventHandlerMovingTests, handle)
{
    auto [timerCalls,
          timerExpectedParamValue,
          movementState,
          expectedResult,
          countCallsHasFastMovement,
          retValHasFastMovement,
          countCallsCalculateAverageInterval] = GetParam();

    eventData.timer = &timer;
    eventData.filamentSensor = &filamentSensor;
    eventData.engineSensor = &engineSensor;

    eventData.movementState = movementState;

    EXPECT_CALL(timer, init(isArgEqual(timerExpectedParamValue))).Times(timerCalls);
    EXPECT_CALL(engineSensor, hasFastMovement).Times(countCallsHasFastMovement).WillOnce(Return(retValHasFastMovement));

    EXPECT_CALL(engineSensor, calculateAverageInterval).Times(countCallsCalculateAverageInterval);
    EXPECT_CALL(filamentSensor, calculateAverageInterval).Times(countCallsCalculateAverageInterval);

    event_type_t actualResult = handler.handle(&eventData);
    EXPECT_EQ(expectedResult, actualResult);
}

// timerCalls, timerExpectedParamValue, movementState, expectedResult, countCallsHasFastMovement, retValHasFastMovement,
// countCallsCalculateAverageInterval
INSTANTIATE_TEST_CASE_P(
    EventHandlerMoving,
    EventHandlerMovingTests,
    ::testing::Values(
        std::make_tuple(0, 0, EVENT_MOVEMENT_STOP, EVENT_NONE, 0, false, 0),
        std::make_tuple(0, 0, EVENT_MOVEMENT_ONLY_FILAMENT, EVENT_MANUAL_FEED, 0, false, 0),
        std::make_tuple(1, 500, EVENT_MOVEMENT_ONLY_ENGINE, EVENT_SUSPECTION_ON_ERROR, 0, false, 0),
        std::make_tuple(0, 0, EVENT_MOVEMENT_FILAMENT_AND_ENGINE, EVENT_MOVING, 1, false, 1),
        std::make_tuple(0, 0, EVENT_MOVEMENT_FILAMENT_AND_ENGINE, EVENT_RETRACTION, 1, true, 0)));
