#include "chapter_05_date_and_time/problem_041_day_of_the_week.h"

#include <date/date.h>
#include <exception>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <ostream>
#include <rtc/chrono.h>


namespace tmcppc::problem_41 {
    date::weekday date_to_weekday(const date::year_month_day& date) {
        if (not date.ok()) {
            throw rtc::chrono::invalid_date_error{ date };
        }
        return date::weekday{ date::sys_days{date} };
    }

    unsigned int weekday_to_number(const date::weekday& wd) {
        return wd.iso_encoding();
    }
}  // namespace tmcppc::problem_41


// Day of the week
//
// Write a function that, given a date, determines the day of the week.
// This function should return a value between 1 (for Monday) and 7 (for Sunday).
void problem_41_main(std::ostream& os) {
    using namespace date::literals;  // 1946_y
    using namespace tmcppc::problem_41;

    auto date_1{ 1946_y / 8 / 11 };
    auto date_2{ 1952_y / 4 / 24 };
    auto date_3{ 1972_y / 7 / 9 };
    auto date_4{ 1977_y / 5 / 23 };

    for (const auto& date : { date_1, date_2, date_3, date_4 }) {
        try {
            auto weekday_number{ weekday_to_number(date_to_weekday(date)) };
            fmt::print(os, "{:04}-{:02}-{:02} was: {} ({})\n",
                int(date.year()), unsigned(date.month()), unsigned(date.day()),
                weekday_number, fmt::weekday(weekday_number));
        } catch (const std::exception& ex) {
            os << "Error: " << ex.what() << "\n";
        }
    }
    os << "\n";
}
