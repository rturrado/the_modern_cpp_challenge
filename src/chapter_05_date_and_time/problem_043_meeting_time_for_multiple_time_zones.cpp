#include "Chapter5_DateAndTime.h"

#include <chrono>
#include <format>
#include <iostream>  // cout
#include <string_view>  // literals
#include <utility>  // pair
#include <vector>

namespace ch = std::chrono; using namespace ch;

using vector_of_participants_and_time_zones = std::vector<std::pair<std::string_view, std::string_view>>;

// This solution is based on the video Welcome To The Time Zone,
// by Howard Hinnant at CppCon 2016: https://youtu.be/Vwd3pduVGKY?t=968
template <typename Duration>
void display_local_meeting_times(
    const ch::zoned_time<Duration>& meeting_zt,
    const vector_of_participants_and_time_zones& participants)
{
    std::cout << "Local meeting times:\n";
    for (auto i{ 0 }; i < participants.size(); ++i)
    {
        const auto& p{ participants[i].first };
        const auto& tz{ participants[i].second };

        std::cout << std::format("\t{:10} {:%F %R %z} {:20}\n", p, ch::zoned_time{ tz, meeting_zt }, tz);
    }
}

// Meeting time for multiple time zones
//
// Write a function that, given a list of meeting participants and their time zones,
// displays the local meeting time for each participant.
void problem_43_main()
{
    using namespace std::literals;

    ch::zoned_time<ch::minutes> meeting_zt{ "Europe/Madrid", ch::sys_days{2021y / October / 23} + 18h };

    auto participants = vector_of_participants_and_time_zones{
        { "Laura"sv, "America/Los_Angeles"sv },
        { "Daniel"sv, "America/Denver"sv },
        { "Norman"sv, "America/New_York"sv },
        { "Leonard"sv, "Europe/London"sv },
        { "Manuel"sv, "Europe/Minsk"sv },
        { "Mary"sv, "Europe/Moscow"sv },
        { "Kaisa"sv, "Asia/Kolkata"sv },
        { "Norbert"sv, "Asia/Novosibirsk"sv },
        { "Samuel"sv, "Asia/Singapore"sv },
        { "Paula"sv, "Australia/Perth"sv },
        { "Susan"sv, "Australia/Sydney"sv },
    };

    display_local_meeting_times(meeting_zt, participants);

    std::cout << "\n";
}
