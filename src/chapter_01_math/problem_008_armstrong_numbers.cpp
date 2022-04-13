#include "chapter_01_math/problem_008_armstrong_numbers.h"
#include "chapter_01_math/digits.h"

#include <cmath>  // pow
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <numeric>  // accumulate
#include <ostream>
#include <string>  // to_string
#include <vector>


// Write a function that determines the Armstrong numbers up to a limit, regardless of their number of digits
// v1: using a std::string for converting a number to a container of digits
std::vector<size_t> armstrong_numbers_up_to_a_limit_v1(size_t n) {
    std::vector<size_t> ret{};

    for (size_t i{ 0 }; i <= n; ++i) {
        // Turn current number into a string
        std::string digits{ std::to_string(i) };

        auto sum_of_powers = std::accumulate(digits.cbegin(), digits.cend(), static_cast<size_t>(0),
            [digits_size = digits.size()](size_t total, size_t digit) {
                return total + static_cast<size_t>(std::pow(digit - '0', digits_size));
            });
        if (i == sum_of_powers) {
            ret.push_back(i);
        }
    }

    return ret;
}


// Write a function that determines the Armstrong numbers up to a limit, regardless of their number of digits
// v2: using digits class for converting a number to a container of digits
std::vector<size_t> armstrong_numbers_up_to_a_limit_v2(size_t n) {
    std::vector<size_t> ret{};

    rtc::math::digits<size_t> digits{};
    for (size_t i{ 0 }; i <= n; ++i, ++digits) {
        auto sum_of_powers = std::accumulate(digits.cbegin(), digits.cend(), static_cast<size_t>(0),
            [digits_size = digits.size()](size_t total, size_t digit) {
                return total + static_cast<size_t>(std::pow(digit, digits_size));
            });
        if (i == sum_of_powers) {
            ret.push_back(i);
        }
    }

    return ret;
}


// Write a function that determines the Armstrong numbers up to a limit, regardless of their number of digits
// v3: book's version
std::vector<int> armstrong_numbers_up_to_a_limit_v3(const int n) {
    std::vector<int> ret{};

    for (int i{ 0 }; i <= n; ++i) {
        std::vector<int> digits;
        int n{ i };
        while (n > 0) {
            digits.push_back(n % 10);
            n = n / 10;
        }

        int arm = std::accumulate(std::begin(digits), std::end(digits), 0,
            [s = digits.size()](const int sum, const int digit) {
                return sum + static_cast<int>(std::pow(digit, s));
            });
        if (i == arm) {
            ret.push_back(i);
        }
    }

    return ret;
}


std::vector<size_t> armstrong_numbers_with_three_digits() {
    std::vector<size_t> ret{};

    for (size_t i{ 1 }; i <= 9; ++i) {
        for (size_t j{ 0 }; j <= 9; ++j) {
            for (size_t k{ 0 }; k <= 9; ++k) {
                size_t n{ i * 100 + j * 10 + k };
                if (n == i * i * i + j * j * j + k * k * k) {
                    ret.push_back(n);
                }
            }
        }
    }

    return ret;
}


void problem_8_main(std::ostream& os) {
    fmt::print(os, "Armstrong numbers with three digits:\n");

    for (auto&& n : armstrong_numbers_with_three_digits()) {
        fmt::print(os, "\t{}\n", n);
    }

    fmt::print(os, "\n");
}

// Armstrong numbers
//
// Write a program that prints all Armstrong numbers with three digits
void problem_8_main() {
    problem_8_main(std::cout);
}
