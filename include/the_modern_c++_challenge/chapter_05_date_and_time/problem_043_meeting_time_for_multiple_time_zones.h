#pragma once

#include <chrono>
#include <date/tz.h>
#include <fmt/format.h>
#include <ostream>
#include <vector>


namespace tmcppc::problem_43 {
    using vector_of_participants_and_time_zones = std::vector<std::pair<std::string_view, std::string_view>>;

    // This solution is based on the video Welcome To The Time Zone,
    // by Howard Hinnant at CppCon 2016: https://youtu.be/Vwd3pduVGKY?t=968
    template <typename Duration>
    void display_local_meeting_times(
        std::ostream& os,
        const date::zoned_time<Duration>& meeting_zt,
        const vector_of_participants_and_time_zones& participants) {

        namespace ch = std::chrono;

        os << "Local meeting times:\n";
        for (size_t i{ 0 }; i < participants.size(); ++i) {
            const auto& [p, tz] { participants[i] };
            const auto& zt{ date::zoned_time<ch::minutes>{ tz, meeting_zt } };

            os << fmt::format("\t{:10} ", p) << date::format("%F %R %z", zt) << fmt::format(" {:20}\n", tz);
        }
    }
}  // namespace tmcppc::problem_43


void problem_43_main(std::ostream& os);
