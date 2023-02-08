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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "events_handler.h"

#include "event/event_handler_none.h"
#include "event/event_handler_waitbeforemoving.h"
#include "event/event_handler_moving.h"
#include "event/event_handler_retraction.h"
#include "event/event_handler_manualfeed.h"
#include "event/event_handler_suspectiononerror.h"
#include "event/event_handler_waitinginerror.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::StrictMock;

class TestEventsHandler : public EventsHandler
{
public:
    handlers_t *getHandlers()
    {
        return this->handlers;
    }
};

class EventsHandlerDefaultMapTests : public ::testing::TestWithParam<std::tuple<event_type_t, EventHandler *>>
{
protected:
    TestEventsHandler eventsHandler;
};

TEST_P(EventsHandlerDefaultMapTests, checkDefaultMap)
{
    auto [eventType,
          expectedResult] = GetParam();

    EventHandler *actualResult;

    EventsHandler::handlers_t *defaultHandlers = eventsHandler.getHandlers();

    actualResult = defaultHandlers->at(eventType);

    EXPECT_EQ(expectedResult, actualResult);
}

// eventType, defaultHandler
INSTANTIATE_TEST_CASE_P(
    EventsHandler,
    EventsHandlerDefaultMapTests,
    ::testing::Values(
        std::make_tuple(EVENT_NONE, &EventHandlerNone::defaultObject),
        std::make_tuple(EVENT_WAIT_BEFORE_MOVING, &EventHandlerWaitBeforeMoving::defaultObject),
        std::make_tuple(EVENT_MOVING, &EventHandlerMoving::defaultObject),
        std::make_tuple(EVENT_RETRACTION, &EventHandlerRetraction::defaultObject),
        std::make_tuple(EVENT_MANUAL_FEED, &EventHandlerManualFeed::defaultObject),
        std::make_tuple(EVENT_SUSPECTION_ON_ERROR, &EventHandlerSuspectionOnError::defaultObject),
        std::make_tuple(EVENT_WAITING_IN_ERROR, &EventHandlerWaitingInError::defaultObject)));

class MockEventHandler : public EventHandler
{
public:
    MOCK_METHOD(event_type_t, handle, (event_data_t *), (override));
};

class EventsHandlerTest : public ::testing::TestWithParam<std::tuple<int, event_type_t, event_type_t, event_type_t, event_type_t>>
{
protected:
    StrictMock<MockEventHandler> mockHandler;

    event_data_t eventData;

    EventsHandler::handlers_t handlersMap;

    EventsHandler eventsHandler;
    EventsHandlerTest() : eventsHandler(&handlersMap) {}
};

TEST_P(EventsHandlerTest, handle)
{
    auto [handlerCountCalls,
          existingHandlerEventType,
          calledHandlerEventType,
          returnedHandlerEventType,
          expectedResult] = GetParam();

    handlersMap[existingHandlerEventType] = &mockHandler;

    eventData.state = calledHandlerEventType;

    EXPECT_CALL(mockHandler, handle(&eventData))
        .Times(handlerCountCalls)
        .WillOnce(Return(returnedHandlerEventType));

    event_type_t actualResult = eventsHandler.handle(&eventData);

    EXPECT_EQ(expectedResult, actualResult);
    EXPECT_EQ(ALARM_STATE_NONE, eventData.alarmState);
}
// handlerCountCalls, existingHandlerEventType, calledHandlerEventType, returnedHandlerEventType, expectedResult

INSTANTIATE_TEST_CASE_P(
    EventsHandler,
    EventsHandlerTest,
    ::testing::Values(
        std::make_tuple(0, EVENT_RETRACTION, EVENT_MOVING, EVENT_MANUAL_FEED, EVENT_NONE),
        std::make_tuple(1, EVENT_NONE, EVENT_NONE, EVENT_SUSPECTION_ON_ERROR, EVENT_SUSPECTION_ON_ERROR),
        std::make_tuple(1, EVENT_RETRACTION, EVENT_RETRACTION, EVENT_MANUAL_FEED, EVENT_MANUAL_FEED),
        std::make_tuple(1, EVENT_SUSPECTION_ON_ERROR, EVENT_SUSPECTION_ON_ERROR, EVENT_WAITING_IN_ERROR, EVENT_WAITING_IN_ERROR)));
