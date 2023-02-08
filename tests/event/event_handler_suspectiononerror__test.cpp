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

#include "event/event_handler_suspectiononerror.h"

class MockEventHandlerSuspectionOnError : public EventHandlerSuspectionOnError
{
public:
    MOCK_METHOD(event_type_t, handleNormalMovement, (event_data_t *), (override));
    MOCK_METHOD(event_type_t, handleErrorneosMovement, (event_data_t *), (override));
};

class EventHandlerSuspectionOnErrorHandleTests : public ::testing::TestWithParam<std::tuple<event_movement_state_t, event_type_t, int, event_type_t, int, event_type_t>>
{
protected:
    event_data_t eventData;
    StrictMock<MockEventHandlerSuspectionOnError> handler;
};

TEST_P(EventHandlerSuspectionOnErrorHandleTests, handle)
{
    auto [movementState,
          expectedResult,
          countCallsHandleNormalMovement,
          retValHandleNormalMovement,
          countCallsHandleErrorneosMovement,
          retValHandleErrorneosMovement] = GetParam();

    eventData.movementState = movementState;
    EXPECT_CALL(handler, handleNormalMovement(isArgEqual((uintptr_t)&eventData))).Times(countCallsHandleNormalMovement).WillOnce(Return(retValHandleNormalMovement));

    EXPECT_CALL(handler, handleErrorneosMovement(isArgEqual((uintptr_t)&eventData))).Times(countCallsHandleErrorneosMovement).WillOnce(Return(retValHandleErrorneosMovement));

    event_type_t actualResult = handler.handle(&eventData);
    EXPECT_EQ(expectedResult, actualResult);
}

// movementState, expectedResult, countCallsHandleNormalMovement, retValHandleNormalMovement,
// countCallsHandleErrorneosMovement, retValHandleErrorneosMovement
INSTANTIATE_TEST_CASE_P(
    EventHandlerSuspectionOnError,
    EventHandlerSuspectionOnErrorHandleTests,
    ::testing::Values(

        std::make_tuple(EVENT_MOVEMENT_STOP, EVENT_MANUAL_FEED, 1, EVENT_MANUAL_FEED, 0, EVENT_MOVING),
        std::make_tuple(EVENT_MOVEMENT_ONLY_FILAMENT, EVENT_MANUAL_FEED, 1, EVENT_MANUAL_FEED, 0, EVENT_MOVING),
        std::make_tuple(EVENT_MOVEMENT_ONLY_ENGINE, EVENT_MOVING, 0, EVENT_MANUAL_FEED, 1, EVENT_MOVING),
        std::make_tuple(EVENT_MOVEMENT_FILAMENT_AND_ENGINE, EVENT_MANUAL_FEED, 1, EVENT_MANUAL_FEED, 0, EVENT_MOVING)));

// ---------------------------------------------------------------------------------------------------------------------

class TestEventHandlerSuspectionOnError : public EventHandlerSuspectionOnError
{
public:
    event_type_t handleNormalMovement(event_data_t *eventData)
    {
        return EventHandlerSuspectionOnError::handleNormalMovement(eventData);
    }
    event_type_t handleErrorneosMovement(event_data_t *eventData)
    {
        return EventHandlerSuspectionOnError::handleErrorneosMovement(eventData);
    }
};

class EventHandlerSuspectionOnErrorNormalMovementTests : public ::testing::TestWithParam<std::tuple<event_movement_state_t, event_type_t, int, bool>>,
                                                         public TestCommonHandler<TestEventHandlerSuspectionOnError>
{
};

TEST_P(EventHandlerSuspectionOnErrorNormalMovementTests, handle)
{
    auto [movementState,
          expectedResult,
          countCallsHasFastMovement,
          retValHasFastMovement] = GetParam();

    eventData.movementState = movementState;

    EXPECT_CALL(engineSensor, hasFastMovement).Times(countCallsHasFastMovement).WillOnce(Return(retValHasFastMovement));

    event_type_t actualResult = handler.handleNormalMovement(&eventData);
    EXPECT_EQ(expectedResult, actualResult);
}

// movementState, expectedResult, countCallsHasFastMovement, retValHasFastMovement
INSTANTIATE_TEST_CASE_P(
    EventHandlerSuspectionOnError,
    EventHandlerSuspectionOnErrorNormalMovementTests,
    ::testing::Values(

        std::make_tuple(EVENT_MOVEMENT_STOP, EVENT_NONE, 0, false),
        std::make_tuple(EVENT_MOVEMENT_ONLY_FILAMENT, EVENT_NONE, 0, false),
        std::make_tuple(EVENT_MOVEMENT_ONLY_ENGINE, EVENT_NONE, 0, false),
        std::make_tuple(EVENT_MOVEMENT_FILAMENT_AND_ENGINE, EVENT_MOVING, 1, false),
        std::make_tuple(EVENT_MOVEMENT_FILAMENT_AND_ENGINE, EVENT_RETRACTION, 1, true)));

// ---------------------------------------------------------------------------------------------------------------------

class EventHandlerSuspectionOnErrorErrorneosMovementTests : public ::testing::Test, public TestCommonHandler<TestEventHandlerSuspectionOnError>
{
};

TEST_F(EventHandlerSuspectionOnErrorErrorneosMovementTests, handleErrorneosMovement_suspectionOnError)
{

    EXPECT_CALL(timer, hasEnded).Times(1).WillOnce(Return(false));

    event_type_t actualResult = handler.handleErrorneosMovement(&eventData);
    EXPECT_EQ(EVENT_SUSPECTION_ON_ERROR, actualResult);
}

TEST_F(EventHandlerSuspectionOnErrorErrorneosMovementTests, handleErrorneosMovement_inError)
{

    EXPECT_CALL(timer, hasEnded).Times(1).WillOnce(Return(true));
    EXPECT_CALL(timer, init(4000)).Times(1);

    event_type_t actualResult = handler.handleErrorneosMovement(&eventData);
    EXPECT_EQ(EVENT_WAITING_IN_ERROR, actualResult);
    EXPECT_EQ(ALARM_STATE_ON, eventData.alarmState);
}
