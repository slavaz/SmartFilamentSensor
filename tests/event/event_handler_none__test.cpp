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

#include "test_common_handler.h"

#include "event/event_handler_none.h"

class EventHandlerNoneTests : public ::testing::TestWithParam<std::tuple<int, int, event_movement_state_t, event_type_t>>, public TestCommonHandler<EventHandlerNone>
{
};

TEST_P(EventHandlerNoneTests, handle)
{
    auto [timerCalls,
          timerExpectedParamValue,
          movementState,
          expectedResult] = GetParam();

    eventData.movementState = movementState;

    EXPECT_CALL(timer, init(isArgEqual(timerExpectedParamValue))).Times(timerCalls);

    event_type_t actualResult = handler.handle(&eventData);
    EXPECT_EQ(expectedResult, actualResult);
}

// timerCalls, timerExpectedParamValue, movementState, expectedResult
INSTANTIATE_TEST_CASE_P(
    EventHandlerNone,
    EventHandlerNoneTests,
    ::testing::Values(
        std::make_tuple(0, 0, EVENT_MOVEMENT_STOP, EVENT_NONE),
        std::make_tuple(1, 300, EVENT_MOVEMENT_ONLY_FILAMENT, EVENT_WAIT_BEFORE_MOVING),
        std::make_tuple(1, 300, EVENT_MOVEMENT_ONLY_ENGINE, EVENT_WAIT_BEFORE_MOVING),
        std::make_tuple(1, 300, EVENT_MOVEMENT_FILAMENT_AND_ENGINE, EVENT_WAIT_BEFORE_MOVING)));
