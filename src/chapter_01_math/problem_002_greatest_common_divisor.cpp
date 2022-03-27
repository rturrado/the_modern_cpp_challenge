#include "chapter_01_math/problem_002_greatest_common_divisor.h"
#include "rtc/console_read.h"  // read_positive_number

#include <fmt/ranges.h>
#include <fmt/ostream.h>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>
#include <utility>  // exchange


size_t gcd(size_t m, size_t n)
{
    if (m == 0 or n == 0) {
        return 1;
    }

    // Sort m and n so that m >= n
    if (m < n) {
        n = std::exchange(m, n);
    }

    for (auto i{n}; i > 1; --i) {
        if ((m % i == 0) and (n % i == 0)) {
            return i;
        }
    }
    return 1;
}


void problem_2_main(std::istream& is, std::ostream& os)
{
    // Read two positive integers
    auto m{ rtc::console::read_positive_number(is, os, "Please enter a first number (starting from 1): ", 1) };
    auto n{ rtc::console::read_positive_number(is, os, "Please enter a second number (starting from 1): ", 1) };

    // Calculate the greatest common divisor
    fmt::print(os, "The greatest common divisor of {} and {} is: {}\n\n", m, n, gcd(m, n));
}


// Greatest common divisor
//
// Write a program that, given two positive integers, will calculate and print the greatest common divisor of the two
void problem_2_main()
{
    problem_2_main(std::cin, std::cout);
}
