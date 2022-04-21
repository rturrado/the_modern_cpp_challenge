#include "Chapter5_DateAndTime.h"

#include <chrono>
#include <format>
#include <iostream>  // cout

// Starting from 1
unsigned int daynum(const std::chrono::year_month_day& date)
{
    namespace ch = std::chrono; using namespace ch;

    return (ch::sys_days{ date } - ch::sys_days{ ch::year_month_day{ date.year() / January / 0 } }).count();
}

// Starting from 1
unsigned int weeknum(const std::chrono::year_month_day& date)
{
    namespace ch = std::chrono; using namespace ch;

    unsigned int ret{ (daynum(date) + 6) / 7 };

    auto wd_jan_1st{ (ch::weekday{ date.year() / January / 1 }).iso_encoding() };  // Mon=1, Tue=2... Sun=7
    auto wd_date{ (ch::weekday{ date }).iso_encoding() };
    if (wd_date < wd_jan_1st) { ret++; }

    return ret;
}

// Day and week of the year
//
// Write a function that, given a date, returns the day of the year (from 1 to 365 or 366 for leap years)
// and another function that, for the same input, returns the calendar week of the year.
void problem_42_main()
{
    namespace ch = std::chrono; using namespace ch;

    auto date_1{ 2020y / December / 31 };
    auto date_2{ 2021y / December / 31 };
    auto date_3{ 2022y / January / 7 };
    auto date_4{ 2022y / January / 8 };
    auto date_5{ 2014y / September / 28 };
    auto date_6{ 2012y / April / 5 };

    for (const auto& date : { date_1, date_2, date_3, date_4, date_5, date_6 })
    {
        std::cout << std::format("{} is the day number {} of the year", date, daynum(date));
        std::cout << std::format(", and in the week number {} of the year.\n", weeknum(date));
    }
    std::cout << "\n";
    for (auto date{ 2012y / January / 1 };
        date < ch::year_month_day{ 2012y / March / 6 };
        date = ch::year_month_day{ ch::sys_days{date} + ch::days{1} })
    {
        std::cout << std::format("{} is the day number {} of the year", date, daynum(date));
        std::cout << std::format(", and in the week number {} of the year.\n", weeknum(date));
    }
    std::cout << "\n";
}
