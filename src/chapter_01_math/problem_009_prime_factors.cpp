#include "chapter_01_math/problem_009_prime_factors.h"
#include "chapter_01_math/math.h"  // prime_factors
#include "rtc/console_read.h"  // read_positive_number
#include "rtc/print.h"

#include <iostream>  // cout

using namespace rtc::print;


// Prime factors of a number
// Write a program that prints the prime factors of a number entered by the user
void problem_9_main()
{
    // Read a positive number
    auto n{ rtc::console::read_positive_number("Please enter a number (starting from 0): ", 0) };

    // Print the prime factors of that number
    std::cout << "The prime factors of " << n << " are: " << prime_factors(n) << "\n\n";
}
