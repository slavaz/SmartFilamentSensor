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
    auto [from, to, expectedResult] = GetParam();
    bool actualResult;

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
// from, to, expectedResult
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
