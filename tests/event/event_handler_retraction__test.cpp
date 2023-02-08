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

#include "event/event_handler_retraction.h"

class EventHandlerRetractionTests : public ::testing::TestWithParam<std::tuple<event_movement_state_t, event_type_t, int, bool>>, public TestCommonHandler<EventHandlerRetraction>
{
};

TEST_P(EventHandlerRetractionTests, handle)
{
    auto [movementState,
          expectedResult,
          countCallsHasFastMovement,
          retValHasFastMovement] = GetParam();

    eventData.movementState = movementState;

    EXPECT_CALL(engineSensor, hasFastMovement).Times(countCallsHasFastMovement).WillOnce(Return(retValHasFastMovement));

    event_type_t actualResult = handler.handle(&eventData);
    EXPECT_EQ(expectedResult, actualResult);
}

// movementState, expectedResult, countCallsHasFastMovement, retValHasFastMovement
INSTANTIATE_TEST_CASE_P(
    EventHandlerRetraction,
    EventHandlerRetractionTests,
    ::testing::Values(
        std::make_tuple(EVENT_MOVEMENT_STOP, EVENT_NONE, 0, false),
        std::make_tuple(EVENT_MOVEMENT_ONLY_FILAMENT, EVENT_NONE, 0, false),
        std::make_tuple(EVENT_MOVEMENT_ONLY_ENGINE, EVENT_NONE, 0, false),
        std::make_tuple(EVENT_MOVEMENT_FILAMENT_AND_ENGINE, EVENT_MOVING, 1, false),
        std::make_tuple(EVENT_MOVEMENT_FILAMENT_AND_ENGINE, EVENT_RETRACTION, 1, true)));
