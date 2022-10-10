#include "chapter_05_date_and_time/problem_041_day_of_the_week.h"

#include <chrono>
#include <exception>
#include <format>
#include <iostream>  // cout
#include <ostream>
#include <rtc/chrono.h>

namespace ch = std::chrono;


namespace tmcppc::problem_41 {
    ch::weekday date_to_weekday(const ch::year_month_day& date) {
        if (not date.ok()) {
            throw rtc::chrono::invalid_date_error{ date };
        }
        return ch::weekday{ std::chrono::sys_days{date} };
    }

    unsigned int weekday_to_number(const ch::weekday& wd) {
        return wd.iso_encoding();
    }
}  // namespace tmcppc::problem_41


// Day of the week
//
// Write a function that, given a date, determines the day of the week.
// This function should return a value between 1 (for Monday) and 7 (for Sunday).
void problem_41_main(std::ostream& os) {
    using namespace std::chrono_literals;
    using namespace tmcppc::problem_41;

    auto date_1{ 1946y / 8 / 11 };
    auto date_2{ 1952y / 4 / 24 };
    auto date_3{ 1972y / 7 / 9 };
    auto date_4{ 1977y / 5 / 23 };

    for (const auto& date : { date_1, date_2, date_3, date_4 }) {
        try {
            auto wd{ date_to_weekday(date) };
            os << std::format("{} was: {} ({})\n", date, weekday_to_number(wd), wd);
        } catch (const std::exception& ex) {
            os << "Error: " << ex.what() << "\n";
        }
    }
    os << "\n";
}
