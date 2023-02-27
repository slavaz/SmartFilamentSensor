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

#include "event_controller.h"

using ::testing::Return;
using ::testing::StrictMock;

class MockSensorManagement : public SensorManagement
{
public:
    MOCK_METHOD(void, init, (MovementSensor *const), (override));
    MOCK_METHOD(void, setReadingDelay, (const uint32_t), (override));
    MOCK_METHOD(void, heartbeat, (), (override));
    MOCK_METHOD(bool, moved, (), (override));
};

class MockTimer : public Timer
{
public:
    MOCK_METHOD(void, heartbeat, (), (override));
};

class MockEventsHandler : public EventsHandler
{
public:
    MOCK_METHOD(event_type_t, handle, (event_data_t *), (override));
};

class MockPinOutput : public PinOutput
{
public:
    MOCK_METHOD(void, set, (bool), (override));
};

class MockRgbLed : public RgbLed
{
public:
    MOCK_METHOD(void, set, (const rgb_t *), (override));
};

class TestEventController : public EventController
{
public:
    TestEventController(SensorManagement *filamentSensor, SensorManagement *engineSensor, Timer *timer, EventsHandler *eventsHandler) : EventController(filamentSensor, engineSensor, timer, eventsHandler) {}

    event_data_t *getEventData()
    {
        return &eventData;
    }
};

class EventControllerTest : public ::testing::TestWithParam<std::tuple<bool, bool, event_type_t, alarm_state_t, const rgb_t *, event_movement_state_t, bool, int>>
{
protected:
    StrictMock<MockSensorManagement> filamentSensorManagement;
    StrictMock<MockSensorManagement> engineSensorManagement;
    StrictMock<MockTimer> timer;
    StrictMock<MockEventsHandler> eventsHandler;
    StrictMock<MockPinOutput> alarm;
    StrictMock<MockRgbLed> rgbLed;

    TestEventController eventController;

    EventControllerTest() : eventsHandler(), eventController(&filamentSensorManagement, &engineSensorManagement,
                                                             &timer, &eventsHandler) {}
};

MATCHER_P(isArgEqual, expected, std::string(negation ? "is" : "isn't") + " match " + std::to_string(expected))
{
    return arg == expected;
}

TEST_P(EventControllerTest, heartbeat)
{
    auto [filamentMoved,
          engineMoved,
          eventType,
          alarmState,
          rgbColor,
          movementState,
          alarmFlag,
          alarmSetCountCalls] = GetParam();

    EXPECT_CALL(filamentSensorManagement, init).Times(1);
    EXPECT_CALL(engineSensorManagement, init).Times(1);
    EXPECT_CALL(filamentSensorManagement, setReadingDelay(5000)).Times(1);
    EXPECT_CALL(engineSensorManagement, setReadingDelay(1000)).Times(1);
    EXPECT_CALL(alarm, set(isArgEqual(false))).Times(1);

    eventController.init(&rgbLed, &alarm, NULL, NULL);

    EXPECT_CALL(timer, heartbeat).Times(1);
    EXPECT_CALL(engineSensorManagement, heartbeat).Times(1);
    EXPECT_CALL(filamentSensorManagement, heartbeat).Times(1);

    EXPECT_CALL(engineSensorManagement, moved).Times(1).WillOnce(Return(engineMoved));
    EXPECT_CALL(filamentSensorManagement, moved).Times(1).WillOnce(Return(filamentMoved));

    EXPECT_CALL(eventsHandler, handle).Times(1).WillOnce(Return(eventType));
    EXPECT_CALL(rgbLed, set(rgbColor)).Times(1);

    EXPECT_CALL(alarm, set(isArgEqual(alarmFlag))).Times(alarmSetCountCalls);

    event_data_t *eventData = eventController.getEventData();
    eventData->alarmState = alarmState;

    eventController.heartbeat();
    EXPECT_EQ(movementState, eventData->movementState);
    EXPECT_EQ(eventType, eventData->state);
}

INSTANTIATE_TEST_CASE_P(
    EventController,
    EventControllerTest,
    ::testing::Values(
        /* Check eventMovement state calculation*/
        std::make_tuple(false, false, EVENT_NONE, ALARM_STATE_NONE, &RgbLed::GREEN, EVENT_MOVEMENT_STOP, false, 0),
        std::make_tuple(true, false, EVENT_NONE, ALARM_STATE_NONE, &RgbLed::GREEN, EVENT_MOVEMENT_ONLY_FILAMENT, false, 0),
        std::make_tuple(false, true, EVENT_NONE, ALARM_STATE_NONE, &RgbLed::GREEN, EVENT_MOVEMENT_ONLY_ENGINE, false, 0),
        std::make_tuple(true, true, EVENT_NONE, ALARM_STATE_NONE, &RgbLed::GREEN, EVENT_MOVEMENT_FILAMENT_AND_ENGINE, false, 0),

        /* Check Rgb Led Color*/
        std::make_tuple(false, false, EVENT_NONE, ALARM_STATE_NONE, &RgbLed::GREEN, EVENT_MOVEMENT_STOP, false, 0),
        std::make_tuple(false, false, EVENT_WAIT_BEFORE_MOVING, ALARM_STATE_NONE, &RgbLed::GREEN, EVENT_MOVEMENT_STOP, false, 0),
        std::make_tuple(false, false, EVENT_MOVING, ALARM_STATE_NONE, &RgbLed::GREEN, EVENT_MOVEMENT_STOP, false, 0),
        std::make_tuple(false, false, EVENT_RETRACTION, ALARM_STATE_NONE, &RgbLed::BLUE, EVENT_MOVEMENT_STOP, false, 0),
        std::make_tuple(false, false, EVENT_MANUAL_FEED, ALARM_STATE_NONE, &RgbLed::YELLOW, EVENT_MOVEMENT_STOP, false, 0),
        std::make_tuple(false, false, EVENT_SUSPECTION_ON_ERROR, ALARM_STATE_NONE, &RgbLed::GREEN, EVENT_MOVEMENT_STOP, false, 0),
        std::make_tuple(false, false, EVENT_WAITING_IN_ERROR, ALARM_STATE_NONE, &RgbLed::RED, EVENT_MOVEMENT_STOP, false, 0),

        /* Check alarming */
        std::make_tuple(false, false, EVENT_NONE, ALARM_STATE_NONE, &RgbLed::GREEN, EVENT_MOVEMENT_STOP, false, 0),
        std::make_tuple(false, false, EVENT_NONE, ALARM_STATE_ON, &RgbLed::GREEN, EVENT_MOVEMENT_STOP, true, 1),
        std::make_tuple(false, false, EVENT_NONE, ALARM_STATE_OFF, &RgbLed::GREEN, EVENT_MOVEMENT_STOP, false, 1)));