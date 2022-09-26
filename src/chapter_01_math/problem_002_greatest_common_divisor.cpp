#include "chapter_01_math/problem_002_greatest_common_divisor.h"

#include "rtc/console.h"  // read_positive_number

#include "fmt/ostream.h"

#include <iostream>  // cin, cout
#include <stdexcept>  // runtime_error
#include <utility>  // exchange


namespace tmcppc::problem_2 {
    int gcd(int m, int n) {
        if (m <= 0 or n <= 0) {
            throw std::runtime_error{ "calling gcd(m, n) with a negative or zero value" };
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
}  // namespace tmcppc::problem_2


void problem_2_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::problem_2;

    auto m{ rtc::console::read_positive_number(is, os, "Please enter a first number (>= 1): ", 1) };
    auto n{ rtc::console::read_positive_number(is, os, "Please enter a second number (>= 1): ", 1) };

    try {
        fmt::print(os, "The greatest common divisor of {} and {} is: {}\n\n", m, n, gcd(m, n));
    } catch (const std::exception& ex) {
        fmt::print(os, "Error: {}.\n\n", ex.what());
    }
}


// Greatest common divisor
//
// Write a program that, given two positive integers, will calculate and print the greatest common divisor of the two
void problem_2_main() {
    problem_2_main(std::cin, std::cout);
}
