#include "chapter_05_date_and_time/problem_042_day_and_week_of_the_year.h"

#include "rtc/chrono.h"

#include <chrono>
#include <format>
#include <iostream>  // cout

namespace ch = std::chrono;
using namespace std::chrono_literals;


namespace tmcppc::problem_42 {
    // Starting from 1
    unsigned int daynum(const ch::year_month_day& date) {
        if (not date.ok()) {
            throw rtc::chrono::invalid_date_error{ date };
        }
        return (ch::sys_days{ date } - ch::sys_days{ ch::year_month_day{ date.year() / ch::January / 0 } }).count();
    }


    // Starting from 1
    unsigned int weeknum(const ch::year_month_day& date) {
        if (not date.ok()) {
            throw rtc::chrono::invalid_date_error{ date };
        }

        unsigned int ret{ (daynum(date) + 6) / 7 };

        auto wd_jan_1st{ (ch::weekday{ date.year() / ch::January / 1 }).iso_encoding() };  // Mon=1, Tue=2... Sun=7
        auto wd_date{ (ch::weekday{ date }).iso_encoding() };
        if (wd_date < wd_jan_1st) {
            ret++;
        }

        return ret;
    }
}  // namespace tmcppc::problem_42


void problem_42_main(std::ostream& os) {
    using namespace tmcppc::problem_42;

    auto date_1{ 2020y / ch::December / 31 };
    auto date_2{ 2021y / ch::December / 31 };
    auto date_3{ 2022y / ch::January / 7 };
    auto date_4{ 2022y / ch::January / 8 };
    auto date_5{ 2014y / ch::September / 28 };
    auto date_6{ 2012y / ch::April / 5 };

    os << "Date\t\tDay number\tWeek number\n";
    for (const auto& date : { date_1, date_2, date_3, date_4, date_5, date_6 }) {
        os << std::format("{}\t{}\t\t{}\n", date, daynum(date), weeknum(date));
    }
    os << "\n";
    for (auto date{ 2012y / ch::February / 24 };
        date < ch::year_month_day{ 2012y / ch::March / 6 };
        date = ch::year_month_day{ ch::sys_days{date} + ch::days{1} }) {

        os << std::format("{}\t{}\t\t{}\n", date, daynum(date), weeknum(date));
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
