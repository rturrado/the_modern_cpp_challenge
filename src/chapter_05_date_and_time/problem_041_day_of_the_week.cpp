#include "Chapter5_DateAndTime.h"

#include <chrono>
#include <format>
#include <iostream>  // cout

unsigned int weekday_to_i(const std::chrono::year_month_day& date)
{
    return std::chrono::weekday{ std::chrono::sys_days{date} }.iso_encoding();
}

// Day of the week
//
// Write a function that, given a date, determines the day of the week.
// This function should return a value between 1 (for Monday) and 7 (for Sunday).
void problem_41_main()
{
    namespace ch = std::chrono; using namespace std::chrono_literals;

    auto date_1{ 1946y / 8 / 11 };
    auto date_2{ 1952y / 4 / 24 };
    auto date_3{ 1972y / 7 / 9 };
    auto date_4{ 1977y / 5 / 23 };

    for (const auto& date : { date_1, date_2, date_3, date_4 })
    {
        std::cout << std::format("{} was: {} ({})\n",
            date,
            weekday_to_i(date),
            ch::weekday{ ch::sys_days{date} });
    }
    std::cout << "\n";
}
