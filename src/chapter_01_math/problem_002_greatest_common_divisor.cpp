#include "chapter_01_math/problem_002_greatest_common_divisor.h"
#include "rtc/console.h"  // read_positive_number

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>
#include <utility>  // exchange


int gcd(std::ostream& os, int m, int n) {
    if (m <= 0 or n <= 0) {
        os << "Error: calling gcd(m, n) with a negative or zero value.\n";
        return -1;
    }

    // Sort m and n so that m >= n
    if (m < n) {
        n = std::exchange(m, n);
    }

    for (auto i{ n }; i > 0; --i) {
        if ((m % i == 0) and (n % i == 0)) {
            return i;
        }
    }
    return -1;
}


int gcd(int m, int n) {
    return gcd(std::cerr, m, n);
}


void problem_2_main(std::istream& is, std::ostream& os) {
    auto m{ rtc::console::read_positive_number(is, os, "Please enter a first number (>= 1): ", 1) };
    auto n{ rtc::console::read_positive_number(is, os, "Please enter a second number (>= 1): ", 1) };

    fmt::print(os, "The greatest common divisor of {} and {} is: {}\n\n", m, n, gcd(os, m, n));
}


// Greatest common divisor
//
// Write a program that, given two positive integers, will calculate and print the greatest common divisor of the two
void problem_2_main() {
    problem_2_main(std::cin, std::cout);
}
