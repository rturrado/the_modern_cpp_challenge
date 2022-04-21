#include "Chapter5_DateAndTime.h"

#include <chrono>
#include <iostream>  // cout
#include <utility>  // pair
#include <vector>

int difference_in_days(std::chrono::sys_days start_date, std::chrono::sys_days end_date)
{
    return (end_date - start_date).count();
}

// Number of days between two dates
//
// Write a function that, given two dates, returns the number of days between the two dates.
// The function should work regardless of the order of the input dates.
void problem_40_main()
{
    namespace ch = std::chrono; using namespace std::chrono_literals;

    auto x{ 2012y / 1 / 24 };
    auto y{ 2013y / 1 / 8 };
    auto a{ 1977y / 5 / 23 };
    auto b{ 2021y / 9 / 23 };

    using vector_of_date_pairs = std::vector<std::pair<ch::year_month_day, ch::year_month_day>>;
    for (const auto& [start_date, end_date] : vector_of_date_pairs{ {x, y}, {y, x}, {a, b}, {b, a} })
    {
        std::cout << "First day: " << start_date << "\n";
        std::cout << "Second day: " << end_date << "\n";
        std::cout << "Difference (in days): " << difference_in_days(start_date, end_date) << "\n";
        std::cout << "\n";
    }
}
