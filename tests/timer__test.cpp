#include <gtest/gtest.h>
#include "mock_time.h"
#include "timer.h"

#define TEST_TIME_WAIT 1000

TEST(Timer, init)
{
    Timer timer;

    mockTime.reset();

    timer.init(TEST_TIME_WAIT);

    EXPECT_EQ(1, mockTime.getCountMethodCalls(MockTimeMethod__get_absolute_time));
}

TEST(Timer, heartbeat)
{
    Timer timer;

    mockTime.reset();

    timer.init(TEST_TIME_WAIT);

    timer.heartbeat();

    EXPECT_EQ(2, mockTime.getCountMethodCalls(MockTimeMethod__get_absolute_time));
}

class TimerHasEndedParametersTests : public ::testing::TestWithParam<std::tuple<int, int, bool>>
{
protected:
    Timer timer;
};

TEST_P(TimerHasEndedParametersTests, ChecksHasEnded)
{
    int from = std::get<0>(GetParam());
    int to = std::get<1>(GetParam());
    bool actualResult, expectedResult = std::get<2>(GetParam());

    mockTime.reset();

    mockTime.setMethodReturnValue(MockTimeMethod__get_absolute_time, from);
    timer.init(TEST_TIME_WAIT);

    mockTime.setMethodReturnValue(MockTimeMethod__get_absolute_time, to);
    timer.heartbeat();
    actualResult = timer.hasEnded();

    EXPECT_EQ(1, mockTime.getCountMethodCalls(MockTimeMethod__absolute_time_diff_us));
    EXPECT_EQ(from, mockTime.getParameter(MockTimeMethodParameter__absolute_time_diff_us__from));
    EXPECT_EQ(to, mockTime.getParameter(MockTimeMethodParameter__absolute_time_diff_us__to));

    EXPECT_EQ(expectedResult, actualResult);
}

INSTANTIATE_TEST_CASE_P(
    Timer,
    TimerHasEndedParametersTests,
    ::testing::Values(
        std::make_tuple(1000000, 1001000, false),
        std::make_tuple(1000000, 1999000, false),
        std::make_tuple(1000000, 2000000, false),
        std::make_tuple(1000000, 2001000, true),
        std::make_tuple(1000000, 1000, true),
        std::make_tuple(0, 11110000, true)));
