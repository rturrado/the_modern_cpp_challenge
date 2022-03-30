#include "chapter_01_math/problem_009_prime_factors.h"
#include "chapter_01_math/math.h"  // prime_factors
#include "rtc/console_read.h"  // read_positive_number
#include "rtc/print.h"

#include <iostream>  // cin, cout
#include <istream>
#include <ostream>

using namespace rtc::print;


void problem_9_main(std::istream& is, std::ostream& os)
{
    // Read a positive number
    auto n{ rtc::console::read_positive_number(is, os, "Please enter a number (>= 0): ", 0) };

    // Print the prime factors of that number
    os << "The prime factors of " << n << " are: " << rtc::math::prime_factors(n) << "\n\n";
}


// Prime factors of a number
//
// Write a program that prints the prime factors of a number entered by the user
void problem_9_main()
{
    problem_9_main(std::cin, std::cout);
}
