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

#include "event/event_handler_waitbeforemoving.h"

class EventHandlerWaitBeforeMovingTests : public ::testing::Test, public TestCommonHandler<EventHandlerWaitBeforeMoving>
{
};

TEST_F(EventHandlerWaitBeforeMovingTests, handle_timerHasNotEnded)
{

    EXPECT_CALL(timer, hasEnded).Times(1).WillOnce(Return(false));

    event_type_t actualResult = handler.handle(&eventData);
    EXPECT_EQ(EVENT_WAIT_BEFORE_MOVING, actualResult);
}

TEST_F(EventHandlerWaitBeforeMovingTests, handle_timerHasEnded)
{

    EXPECT_CALL(timer, hasEnded).Times(1).WillOnce(Return(true));
    EXPECT_CALL(filamentSensor, reset).Times(1);
    EXPECT_CALL(engineSensor, reset).Times(1);

    event_type_t actualResult = handler.handle(&eventData);
    EXPECT_EQ(EVENT_MOVING, actualResult);
}
