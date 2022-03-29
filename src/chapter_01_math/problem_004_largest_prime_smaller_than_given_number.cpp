#include "chapter_01_math/problem_004_largest_prime_smaller_than_given_number.h"
#include "chapter_01_math/math.h"  // is_prime
#include "rtc/console_read.h"  // read_positive_number

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>


size_t biggest_prime_smaller_than(const size_t n)
{
    if (n == 0 or n == 1) { return 0; }
    return (is_prime(n - 1) ? n - 1 : biggest_prime_smaller_than(n - 1));
};


void problem_4_main(std::istream& is, std::ostream& os)
{
    auto limit{ rtc::console::read_positive_number(is, os, "Please enter a number (>= 2): ", 2) };

    fmt::print(os, "Biggest prime number smaller than {} is: {}\n\n", limit, biggest_prime_smaller_than(limit));
}


// Largest prime smaller than given number
//
// Write a program that computes and prints the largest prime number
// that is smaller than a number provided by the user, which must be a positive integer
void problem_4_main()
{
    problem_4_main(std::cin, std::cout);
}
