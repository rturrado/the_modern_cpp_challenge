#include "chapter_05_date_and_time/problem_042_day_and_week_of_the_year.h"

#include <chrono>
#include <date/date.h>
#include <fmt/format.h>
#include <iostream>  // cout
#include <rtc/chrono.h>

using namespace date::literals;  // 2020_y


namespace tmcppc::problem_42 {
    // Starting from 1
    unsigned int daynum(const date::year_month_day& date) {
        if (not date.ok()) {
            throw rtc::chrono::invalid_date_error{ date };
        }
        return (date::sys_days{ date } - date::sys_days{ date::year_month_day{ date.year() / date::January / 0 } }).count();
    }


    // Starting from 1
    unsigned int weeknum(const date::year_month_day& date) {
        if (not date.ok()) {
            throw rtc::chrono::invalid_date_error{ date };
        }

        unsigned int ret{ (daynum(date) + 6) / 7 };

        auto wd_jan_1st{ (date::weekday{ date.year() / date::January / 1 }).iso_encoding() };  // Mon=1, Tue=2... Sun=7
        auto wd_date{ (date::weekday{ date }).iso_encoding() };
        if (wd_date < wd_jan_1st) {
            ret++;
        }

        return ret;
    }
}  // namespace tmcppc::problem_42


void problem_42_main(std::ostream& os) {
    using namespace tmcppc::problem_42;

    auto date_1{ 2020_y / date::December / 31 };
    auto date_2{ 2021_y / date::December / 31 };
    auto date_3{ 2022_y / date::January / 7 };
    auto date_4{ 2022_y / date::January / 8 };
    auto date_5{ 2014_y / date::September / 28 };
    auto date_6{ 2012_y / date::April / 5 };

    os << "Date\t\tDay number\tWeek number\n";
    for (const auto& date : { date_1, date_2, date_3, date_4, date_5, date_6 }) {
        os << date << fmt::format("\t{}\t\t{}\n", daynum(date), weeknum(date));
    }
    os << "\n";
    for (auto date{ 2012_y / date::February / 24 };
        date < date::year_month_day{ 2012_y / date::March / 6 };
        date = date::year_month_day{ date::sys_days{date} + date::days{1} }) {

        os << date << fmt::format("\t{}\t\t{}\n", daynum(date), weeknum(date));
    }
    os << "\n";
}


// Day and week of the year
//
// Write a function that, given a date, returns the day of the year (from 1 to 365 or 366 for leap years)
// and another function that, for the same input, returns the calendar week of the year.
void problem_42_main() {
    problem_42_main(std::cout);
}
