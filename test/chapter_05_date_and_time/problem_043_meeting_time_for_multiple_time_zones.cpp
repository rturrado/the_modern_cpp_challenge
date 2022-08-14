#include "chapter_05_date_and_time/problem_043_meeting_time_for_multiple_time_zones.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <sstream>  // ostringstream

namespace ch = std::chrono;
using namespace std::chrono_literals;
using namespace tmcppc::problem_43;


TEST(display_local_meeting_times, DISABLED_no_participants) {
    std::ostringstream oss{};
    ch::zoned_time<ch::minutes> meeting_zt{ "Europe/Madrid", ch::sys_days{2021y / ch::October / 23} + 18h };
    vector_of_participants_and_time_zones participants{};
    display_local_meeting_times(oss, meeting_zt, participants);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Local meeting times:\n"));
}


TEST(display_local_meeting_times, DISABLED_some_participants) {
    std::ostringstream oss{};
    ch::zoned_time<ch::minutes> meeting_zt{ "Europe/Madrid", ch::sys_days{2021y / ch::October / 23} + 18h };
    auto participants = vector_of_participants_and_time_zones{
        { "Laura", "America/Los_Angeles" },
        { "Daniel", "America/Denver" }
    };
    display_local_meeting_times(oss, meeting_zt, participants);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Local meeting times:\n"
        "\tLaura      2021-10-23 11:00 -0700 America/Los_Angeles \n"
        "\tDaniel     2021-10-23 12:00 -0600 America/Denver      \n"
    ));
}


TEST(problem_43_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_43_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Local meeting times:\n"
        "\tLaura      2021-10-23 11:00 -0700 America/Los_Angeles \n"
        "\tDaniel     2021-10-23 12:00 -0600 America/Denver      \n"
        "\tNorman     2021-10-23 14:00 -0400 America/New_York    \n"
        "\tLeonard    2021-10-23 19:00 +0100 Europe/London       \n"
        "\tManuel     2021-10-23 21:00 +0300 Europe/Minsk        \n"
        "\tMary       2021-10-23 21:00 +0300 Europe/Moscow       \n"
        "\tKaisa      2021-10-23 23:30 +0530 Asia/Kolkata        \n"
        "\tNorbert    2021-10-24 01:00 +0700 Asia/Novosibirsk    \n"
        "\tSamuel     2021-10-24 02:00 +0800 Asia/Singapore      \n"
        "\tPaula      2021-10-24 02:00 +0800 Australia/Perth     \n"
        "\tSusan      2021-10-24 05:00 +1100 Australia/Sydney    \n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}

