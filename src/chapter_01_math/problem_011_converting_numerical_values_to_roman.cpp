#include "chapter_01_math/problem_011_converting_numerical_values_to_roman.h"
#include "chapter_01_math/roman.h"
#include "rtc/console_read.h"  // read_positive_number

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>


void problem_11_main(std::istream& is, std::ostream& os)
{
    using namespace rtc::date;

    auto message{ fmt::format("Please enter a number (between 1 and {}): ", max_roman_numeral) };
    auto n{ rtc::console::read_positive_number(is, os, message, 1, max_roman_numeral + 1) };

    fmt::print(os, "Number\tRoman numeral equivalent\n");
    fmt::print(os, "{}\t{}\n\n", n, to_roman_v1(n));
}


// Converting numerical values to Roman
//
// Write a program that, given a number entered by the user, prints its Roman numeral equivalent
void problem_11_main()
{
    problem_11_main(std::cin, std::cout);
}
