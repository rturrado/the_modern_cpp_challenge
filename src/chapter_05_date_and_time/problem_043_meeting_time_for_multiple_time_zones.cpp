#include "chapter_05_date_and_time/problem_043_meeting_time_for_multiple_time_zones.h"

#include <chrono>
#include <date/date.h>
#include <date/tz.h>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <string_view>  // literals


// Meeting time for multiple time zones
//
// Write a function that, given a list of meeting participants and their time zones,
// displays the local meeting time for each participant.
void problem_43_main(std::ostream& os) {
    namespace ch = std::chrono;
    using namespace date::literals;  // 2021_y
    using namespace std::chrono_literals;  // 18h
    using namespace tmcppc::problem_43;

    date::zoned_time<ch::minutes> meeting_zt{ "Europe/Madrid", date::sys_days{2021_y / date::October / 23} + 18h };

    auto participants = vector_of_participants_and_time_zones{
        { "Laura", "America/Los_Angeles" },
        { "Daniel", "America/Denver" },
        { "Norman", "America/New_York" },
        { "Leonard", "Europe/London" },
        { "Manuel", "Europe/Minsk" },
        { "Mary", "Europe/Moscow" },
        { "Kaisa", "Asia/Kolkata" },
        { "Norbert", "Asia/Novosibirsk" },
        { "Samuel", "Asia/Singapore" },
        { "Paula", "Australia/Perth" },
        { "Susan", "Australia/Sydney" },
    };

    display_local_meeting_times(os, meeting_zt, participants);

    fmt::print(os, "\n");
}
