#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "mock_time.h"

#include "sensor_management.h"
#include "movement_sensor.h"

using ::testing::AnyNumber;
using ::testing::AtLeast;
using ::testing::Return;

class TestSensorManagement : public SensorManagement
{
public:
    uint getAverageIntervalBetweenEvents() { return this->averageIntervalBetweenEvents; }
    void setAverageIntervalBetweenEvents(uint interval) { this->averageIntervalBetweenEvents = interval; }
    time_t getLastMovementTime() { return this->lastMovementTime; }
    void setLastMovementTime(time_t time) { this->lastMovementTime = time; }
    uint getPreviousDifferenceMillisec() { return this->previousDifferenceMillisec; }
    void setPreviousDifferenceMillisec(uint difference) { this->previousDifferenceMillisec = difference; }
    void setDifferenceMillisec(uint difference) { this->differenceMillisec = difference; }
};

class MockMovementSensor : public MovementSensor
{
public:
    MOCK_METHOD(void, init, (const uint gpio), (override));
    MOCK_METHOD(bool, hasMovement, (), (override));

    uint getPin()
    {
        return this->pin;
    }
    bool getOldValue()
    {
        return this->oldValue;
    }
};

class SensorManagementMovedParametersTests : public ::testing::TestWithParam<std::tuple<uint, uint, uint, bool, bool, time_t, uint>>
{
protected:
    TestSensorManagement sensorManagement;
};

TEST_P(SensorManagementMovedParametersTests, moved)
{
    auto [firstTime,
          lastTime,
          readingDelay,
          hasMovement,
          expectedResult,
          expectedLastMovementTime,
          expectedPreviousDifferenceMillisec] = GetParam();

    bool actualResult;

    MockMovementSensor mockMovementSensor;

    mockTime.reset();

    mockTime.setMethodReturnValue(MockTimeMethod__get_absolute_time, firstTime);

    sensorManagement.init(&mockMovementSensor);
    sensorManagement.setReadingDelay(readingDelay);

    EXPECT_CALL(mockMovementSensor, hasMovement())
        .Times(AtLeast(1))
        .WillOnce(Return(hasMovement));

    mockTime.setMethodReturnValue(MockTimeMethod__get_absolute_time, lastTime);
    sensorManagement.heartbeat();

    actualResult = sensorManagement.moved();
    EXPECT_EQ(expectedResult, actualResult);
    EXPECT_EQ(expectedLastMovementTime, sensorManagement.getLastMovementTime());
    EXPECT_EQ(expectedPreviousDifferenceMillisec, sensorManagement.getPreviousDifferenceMillisec());
}

// firstTime, lastTime, readingDelay, hasMovement, expectedResult, expectedLastMovementTime, expectedPreviousDifferenceMillisec
INSTANTIATE_TEST_CASE_P(
    SensorManagement,
    SensorManagementMovedParametersTests,
    ::testing::Values(
        std::make_tuple(1000, 2000, 10, true, true, 2000, 1),
        std::make_tuple(1000, 10000, 10, false, true, 1000, 10),
        std::make_tuple(1000, 11000, 10, false, false, 1000, 10),
        std::make_tuple(1000, 20000, 10, true, true, 20000, 19),
        std::make_tuple(1000, 20000, 10, false, false, 1000, 10)));

class SensorManagementCalculateAverageIntervalParametersTests : public ::testing::TestWithParam<std::tuple<std::vector<uint>, uint>>
{
protected:
    TestSensorManagement sensorManagement;
};

TEST_P(SensorManagementCalculateAverageIntervalParametersTests, calculateAverageInterval)
{
    auto [intervals, expectedResult] = GetParam();

    bool actualResult;
    uint currentTime = 10000;

    MockMovementSensor mockMovementSensor;

    mockTime.reset();

    mockTime.setMethodReturnValue(MockTimeMethod__get_absolute_time, currentTime);

    sensorManagement.init(&mockMovementSensor);

    EXPECT_CALL(mockMovementSensor, hasMovement())
        .Times(AnyNumber())
        .WillOnce(Return(false));

    sensorManagement.setLastMovementTime(10000);
    for (auto difference : intervals)
    {
        currentTime += difference;
        mockTime.setMethodReturnValue(MockTimeMethod__get_absolute_time, currentTime);
        sensorManagement.heartbeat();
        sensorManagement.calculateAverageInterval();
    }
    EXPECT_EQ(expectedResult, sensorManagement.getAverageIntervalBetweenEvents());
}

// firstTime, lastTime, readingDelay, hasMovement, expectedResult
INSTANTIATE_TEST_CASE_P(
    SensorManagement,
    SensorManagementCalculateAverageIntervalParametersTests,
    ::testing::Values(
        std::make_tuple(std::vector<uint>{10000, 0, 0, 0}, 10),
        std::make_tuple(std::vector<uint>{10000, 10000}, 15),
        std::make_tuple(std::vector<uint>{10000, 10000, 0}, 16),
        std::make_tuple(std::vector<uint>{10000, 10000, 0, 0}, 17),
        std::make_tuple(std::vector<uint>{10000, 10000, 20000, 20000}, 32),
        std::make_tuple(std::vector<uint>{15000, 2000, 4000, 5000}, 19),
        std::make_tuple(std::vector<uint>{0, 0, 0, 0}, 0)));

class SensorManagementHasFastMovementParametersTests : public ::testing::TestWithParam<std::tuple<uint, uint, uint, bool>>
{
protected:
    TestSensorManagement sensorManagement;
};

TEST_P(SensorManagementHasFastMovementParametersTests, hasFastMovement)
{
    auto [averageIntervalBetweenEvents,
          differenceMillisec,
          previousDifferenceMillisec,
          expectedResult] = GetParam();

    bool actualResult;

    sensorManagement.setAverageIntervalBetweenEvents(averageIntervalBetweenEvents);
    sensorManagement.setDifferenceMillisec(differenceMillisec);
    sensorManagement.setPreviousDifferenceMillisec(previousDifferenceMillisec);

    actualResult = sensorManagement.hasFastMovement();
    EXPECT_EQ(expectedResult, actualResult);
}

// averageIntervalBetweenEvents, differenceMillisec, previousDifferenceMillisec, expectedResult
INSTANTIATE_TEST_CASE_P(
    SensorManagement,
    SensorManagementHasFastMovementParametersTests,
    ::testing::Values(
        std::make_tuple(100, 0, 0, true),
        std::make_tuple(100, 19, 19, true),
        std::make_tuple(100, 19, 20, false),
        std::make_tuple(100, 20, 19, false),
        std::make_tuple(0, 1, 1, false)));