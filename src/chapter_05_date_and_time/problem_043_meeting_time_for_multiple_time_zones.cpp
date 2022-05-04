#include "chapter_05_date_and_time/problem_043_meeting_time_for_multiple_time_zones.h"

#include <chrono>
#include <iostream>  // cout
#include <ostream>
#include <string_view>  // literals
#include <utility>  // pair
#include <vector>

namespace ch = std::chrono; using namespace ch;


void problem_43_main(std::ostream& os) {
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

    display_local_meeting_times(os, meeting_zt, participants);

    os << "\n";
}


// Meeting time for multiple time zones
//
// Write a function that, given a list of meeting participants and their time zones,
// displays the local meeting time for each participant.
void problem_43_main() {
    problem_43_main(std::cout);
}
