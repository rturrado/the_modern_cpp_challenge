#include "Chapter5_DateAndTime.h"

#include <chrono>
#include <format>
#include <iostream>  // cout
#include <utility>  // pair
#include <vector>

namespace ch = std::chrono; using namespace ch;

void print_calendar_month(const ch::year& y, const ch::month& m)
{
    // Header
    std::cout << ch::year_month{ y / m } << "\n";
    for (unsigned int i{ 1 }; i <= 7; ++i) { std::cout << std::format("{:>4}", ch::weekday{i}); }
    std::cout << "\n";

    // Blank days
    unsigned int y_m_1_iso_wd{ (ch::weekday{y / m / 1}).iso_encoding() - 1 };
    for (unsigned int i{ 0 }; i < y_m_1_iso_wd; ++i) { std::cout << std::format("{:>4}", ' '); }

    // Month days
    unsigned int y_m_d_last{ ch::year_month_day_last{y / m / ch::last}.day() };
    for (unsigned int i{ 1 }; i <= y_m_d_last; ++i)
    {
        std::cout << std::format("{:>4}", i);
        if ((i != y_m_d_last) and ((y_m_1_iso_wd + i) % 7 == 0)) { std::cout << "\n"; }
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
void problem_44_main()
{
    using vector_of_pairs_year_month = std::vector<std::pair<ch::year, ch::month>>;

    for (const auto& [year, month] : vector_of_pairs_year_month{ {1970y, January}, {1977y, May}, {2012y, February} })
    {
        print_calendar_month(year, month);
        std::cout << "\n\n";
    }
}
