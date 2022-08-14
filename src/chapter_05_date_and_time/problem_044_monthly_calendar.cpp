#include "chapter_05_date_and_time/problem_044_monthly_calendar.h"

#include "rtc/chrono.h"

#include <chrono>
#include <format>
#include <iostream>  // cout
#include <ostream>
#include <utility>  // pair
#include <vector>

namespace ch = std::chrono;


namespace tmcppc::problem_44 {
    void print_calendar_month(std::ostream& os, const ch::year& y, const ch::month& m) {
        if (not m.ok()) {
            throw rtc::chrono::invalid_month_error{ m };
        }

        // Header
        os << ch::year_month{ y / m } << "\n";
        for (unsigned int i{ 1 }; i <= 7; ++i) {
            os << std::format("{:>4}", ch::weekday{ i });
        }
        os << "\n";

        // Blank days
        unsigned int y_m_1_iso_wd{ (ch::weekday{y / m / 1}).iso_encoding() - 1 };
        for (unsigned int i{ 0 }; i < y_m_1_iso_wd; ++i) {
            os << std::format("{:>4}", ' ');
        }

        // Month days
        unsigned int y_m_d_last{ ch::year_month_day_last{y / m / ch::last}.day() };
        for (unsigned int i{ 1 }; i <= y_m_d_last; ++i) {
            os << std::format("{:>4}", i);
            if ((i != y_m_d_last) and ((y_m_1_iso_wd + i) % 7 == 0)) {
                os << "\n";
            }
        }
    }
}  // namespace tmcppc::problem_44


void problem_44_main(std::ostream& os) {
    using namespace std::chrono_literals;
    using namespace tmcppc::problem_44;

    using vector_of_pairs_year_month = std::vector<std::pair<ch::year, ch::month>>;

    for (const auto& [year, month] : vector_of_pairs_year_month{ {1970y, ch::January}, {1977y, ch::May}, {2012y, ch::February} }) {
        print_calendar_month(os, year, month);
        os << "\n\n";
    }
}


// Monthly calendar
//
// Write a function that, given a year and a month, prints to the console the month calendar.
// The expected output format is as follows (the example is for December 2017):
//
//    Mon Tue Wed Thu Fri Sat Sun
//                      1   2   3
//      4   5   6   7   8   9  10
//     11  12  13  14  15  16  17
//     18  19  20  21  22  23  24
//     25  26  27  28  29  30  31
void problem_44_main() {
    problem_44_main(std::cout);
}
