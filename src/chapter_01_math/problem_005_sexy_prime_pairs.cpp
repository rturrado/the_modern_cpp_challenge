#include "chapter_01_math/problem_005_sexy_prime_pairs.h"
#include "chapter_01_math/math.h"  // is_prime
#include "rtc/console_read.h"  // read_positive_number

#include <iostream>  // cin, cout
#include <istream>
#include <ostream>


void problem_5_main(std::istream& is, std::ostream& os)
{
    // Read limit
    auto limit{ rtc::console::read_positive_number(is, os, "Please enter a number (>= 1): ", 1) };

    // Print sexy prime pairs up to the limit
    os << "Sexy prime pairs up to " << limit << ":\n";
    for (auto i{7}; i <= limit; ++i)
    {
        if (is_prime(i) && is_prime(i - 6))
        {
            os << "\t{" << i - 6 << ", " << i << "}\n";
        }
    }
    os << "\n";
}


// Sexy prime pairs
//
// Write a program that prints all sexy prime pairs up to a limit entered by the user
void problem_5_main()
{
    problem_5_main(std::cin, std::cout);
}
