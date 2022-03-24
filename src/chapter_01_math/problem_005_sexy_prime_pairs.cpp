#include "problem_005_sexy_prime_pairs.h"
#include "math.h"  // is_prime

#include "rtc/console_read.h"  // read_positive_number

#include <iostream>  // cout


// Sexy prime pairs
//
// Write a program that prints all sexy prime pairs up to a limit entered by the user
void problem_5_main()
{
    // Read limit
    auto limit{ rtc::console::read_positive_number("Please enter a number (starting from 1): ", 1) };

    // Print sexy prime pairs up to the limit
    std::cout << "Sexy prime pairs up to " << limit << ":\n";
    for (auto i = 7u; i <= limit; ++i)
    {
        if (is_prime(i) && is_prime(i - 6))
        {
            std::cout << "\t{" << i - 6 << ", " << i << "}\n";
        }
    }
    std::cout << "\n";
}
