#include "chapter_01_math/problem_008_armstrong_numbers.h"
#include "chapter_01_math/digits.h"

#include <fmt/ranges.h>
#include <fmt/ostream.h>
#include <cmath>  // pow
#include <iostream>  // cout
#include <numeric>  // accumulate
#include <ostream>
#include <string>  // to_string
#include <vector>


// Write a function that determines the Armstrong numbers up to a limit, regardless of their number of digits
// v1: using a std::string for converting a number to a container of digits
void print_armstrong_numbers_up_to_a_limit_v1(std::ostream& os, size_t n, bool print_results)
{
    // Print Armstrong numbers
    if (print_results) {
        fmt::print(os, "Armstrong numbers up to {}:\n", n);
    }
    for (size_t i{ 0 }; i <= n; ++i) {
        // Turn current number into a string
        std::string digits{ std::to_string(i) };

        auto sum_of_powers = std::accumulate(digits.cbegin(), digits.cend(), static_cast<size_t>(0),
            [digits_size = digits.size()](size_t total, size_t digit) {
                return total + static_cast<size_t>(std::pow(digit - '0', digits_size));
            });
        if (i == sum_of_powers) {
            if (print_results) {
                fmt::print(os, "\t{}\n", i);
            }
        }
    }
}

void print_armstrong_numbers_up_to_a_limit_v1(size_t n, bool print_results) {
    print_armstrong_numbers_up_to_a_limit_v1(std::cout, n, print_results);
}


// Write a function that determines the Armstrong numbers up to a limit, regardless of their number of digits
// v2: using digits class for converting a number to a container of digits
void print_armstrong_numbers_up_to_a_limit_v2(std::ostream& os, size_t n, bool print_results)
{
    // Turn current number into a deque of numbers
    rtc::math::digits<size_t> digits{};

    // Print Armstrong numbers
    if (print_results) {
        fmt::print(os, "Armstrong numbers up to {}:\n", n);
    }
    for (size_t i{ 0 }; i <= n; ++i, ++digits) {
        auto sum_of_powers = std::accumulate(digits.cbegin(), digits.cend(), static_cast<size_t>(0),
            [digits_size = digits.size()](size_t total, size_t digit) {
                return total + static_cast<size_t>(std::pow(digit, digits_size));
            });
        if (i == sum_of_powers) {
            if (print_results) {
                fmt::print(os, "\t{}\n", i);
            }
        }
    }
}

void print_armstrong_numbers_up_to_a_limit_v2(size_t n, bool print_results) {
    print_armstrong_numbers_up_to_a_limit_v2(std::cout, n, print_results);
}


// Write a function that determines the Armstrong numbers up to a limit, regardless of their number of digits
// v3: book's version
void print_armstrong_numbers_up_to_a_limit_v3(std::ostream& os, const int n, bool print_results)
{
    if (print_results) {
        fmt::print(os, "Armstrong numbers up to {}:\n", n);
    }
    for (int i{ 0 }; i <= n; ++i) {
        std::vector<int> digits;
        int n = i;
        while (n > 0) {
            digits.push_back(n % 10);
            n = n / 10;
        }

        int arm = std::accumulate(
            std::begin(digits), std::end(digits),
            0,
            [s = digits.size()](const int sum, const int digit) {return sum + static_cast<int>(std::pow(digit, s)); });

        if (i == arm) {
            if (print_results) {
                fmt::print(os, "\t{}\n", i);
            }
        }
    }
}

void print_armstrong_numbers_up_to_a_limit_v3(const int n, bool print_results) {
    print_armstrong_numbers_up_to_a_limit_v3(std::cout, n, print_results);
}



void print_armstrong_numbers_with_three_digits(std::ostream& os)
{
    fmt::print(os, "Armstrong numbers with three digits:\n");
    for (int i{ 1 }; i <= 9; ++i) {
        for (int j{ 0 }; j <= 9; ++j) {
            for (int k{ 0 }; k <= 9; ++k) {
                int n{ i * 100 + j * 10 + k };
                if (n == i * i * i + j * j * j + k * k * k) {
                    std::cout << "\t" << n << "\n";
                }
            }
        }
    }
}

void print_armstrong_numbers_with_three_digits() {
    print_armstrong_numbers_with_three_digits(std::cout);
}


void problem_8_main(std::ostream& os) {
    print_armstrong_numbers_with_three_digits(os);
    os << "\n";
}

// Armstrong numbers
//
// Write a program that prints all Armstrong numbers with three digits
void problem_8_main() {
    problem_8_main(std::cout);
}
