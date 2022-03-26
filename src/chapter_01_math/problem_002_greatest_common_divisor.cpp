#include "chapter_01_math/problem_002_greatest_common_divisor.h"
#include "rtc/console_read.h"  // read_positive_number

#include <iostream>  // cout


size_t gcd(const size_t m, const size_t n)
{
    size_t i{ 1 };
    for (i = n; i > 1; --i)
    {
        if ((m % i == 0) && (n % i == 0))
        {
            return i;
        }
    }
    return i;
}


// Greatest common divisor
//
// Write a program that, given two positive integers, will calculate and print the greatest common divisor of the two
void problem_2_main()
{
    // Read two positive integers
    auto m{ rtc::console::read_positive_number("Please enter a first number (starting from 1): ", 1) };
    auto n{ rtc::console::read_positive_number("Please enter a second number (starting from 1): ", 1) };

    // Sort m and n so that m >= n
    if (m < n)
    {
        auto temp{ m };
        m = n;
        n = temp;
    }

    // Calculate the greatest common divisor
    std::cout << "The greatest common divisor of " << m << " and " << n << " is: " << gcd(m, n) << "\n\n";
}
