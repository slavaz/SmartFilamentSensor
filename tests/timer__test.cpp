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

#include "mocklib/mocklib.h"

#include "timer.h"

using ::testing::AtLeast;
using ::testing::Eq;
using ::testing::Return;

#define TEST_TIME_WAIT 1000

TEST(Timer, init)
{
    MockPicoSdk mockPicoSdk;
    mockPicoSdkApi.mockPicoSdk = &mockPicoSdk;

    Timer timer;

    EXPECT_CALL(mockPicoSdk, get_absolute_time)
        .Times(1);

    timer.init(TEST_TIME_WAIT);
}

TEST(Timer, heartbeat)
{
    MockPicoSdk mockPicoSdk;
    mockPicoSdkApi.mockPicoSdk = &mockPicoSdk;

    Timer timer;

    EXPECT_CALL(mockPicoSdk, get_absolute_time).Times(2);

    timer.init(TEST_TIME_WAIT);
    timer.heartbeat();
}

class TimerHasEndedParametersTests : public ::testing::TestWithParam<std::tuple<int, int, bool>>
{
protected:
    Timer timer;
};

TEST_P(TimerHasEndedParametersTests, ChecksHasEnded)
{
    MockPicoSdk mockPicoSdk;
    mockPicoSdkApi.mockPicoSdk = &mockPicoSdk;

    auto [from, to, expectedResult] = GetParam();
    bool actualResult;

    EXPECT_CALL(mockPicoSdk, get_absolute_time).Times(AtLeast(2)).WillOnce(Return(from)).WillOnce(Return(to));
    EXPECT_CALL(mockPicoSdk, absolute_time_diff_us(Eq(from), Eq(to))).Times(1).WillOnce(Return(to - from));

    timer.init(TEST_TIME_WAIT);

    timer.heartbeat();

    actualResult = timer.hasEnded();

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
