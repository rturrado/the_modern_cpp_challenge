#include "chapter_05_date_and_time/problem_044_monthly_calendar.h"

#include <date/date.h>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <iostream>  // cout
#include <ostream>
#include <rtc/chrono.h>
#include <utility>  // pair
#include <vector>


namespace tmcppc::problem_44 {
    void print_calendar_month(std::ostream& os, const date::year& y, const date::month& m) {
        if (not m.ok()) {
            throw rtc::chrono::invalid_month_error{ m };
        }

        // Header
        os << date::year_month{ y / m } << "\n";
        for (unsigned int i{ 1 }; i <= 7; ++i) {
            os << fmt::format(" {}", fmt::weekday{ i });
        }
        os << "\n";

        // Blank days
        unsigned int y_m_1_iso_wd{ (date::weekday{y / m / 1}).iso_encoding() - 1 };
        for (unsigned int i{ 0 }; i < y_m_1_iso_wd; ++i) {
            os << fmt::format("{:>4}", ' ');
        }

        // Month days
        unsigned int y_m_d_last{ date::year_month_day_last{y / m / date::last}.day() };
        for (unsigned int i{ 1 }; i <= y_m_d_last; ++i) {
            os << fmt::format("{:>4}", i);
            if ((i != y_m_d_last) and ((y_m_1_iso_wd + i) % 7 == 0)) {
                os << "\n";
            }
        }
    }
}  // namespace tmcppc::problem_44


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
void problem_44_main(std::ostream& os) {
    using namespace date::literals;
    using namespace tmcppc::problem_44;

    auto pairs_years_months = std::vector<std::pair<date::year, date::month>>{
        {1970_y, date::January},
        {1977_y, date::May},
        {2012_y, date::February}
    };

    for (const auto& [year, month] : pairs_years_months) {
        print_calendar_month(os, year, month);
        os << "\n\n";
    }
}
