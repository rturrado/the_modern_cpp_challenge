#include "chapter_01_math/problem_006_abundant_numbers.h"
#include "chapter_01_math/math.h"  // divisors
#include "rtc/console_read.h"  // read_positive_number
#include "rtc/print.h"

#include <iostream>  // cin, cout
#include <istream>
#include <numeric>  // accumulate
#include <ostream>

using namespace rtc::print;


void problem_6_main(std::istream& is, std::ostream& os)
{
    // Read limit
    auto limit{ rtc::console::read_positive_number(is, os, "Please enter a number (starting from 1): ", 1) };

    // Print abundant numbers up to the limit and their abundance
    os << "Abudant numbers up to " << limit << ", {list of divisors}, (and their abundance):\n";
    for (auto i{1}; i <= limit; ++i)
    {
        auto d = divisors(i);
        auto sum = std::accumulate(d.cbegin(), d.cend(), 0);
        if (sum > i)
        {
            os << "\t"<< i << " " << d << " (" << sum - i << ")\n";
        }
    }
    os << "\n";
}


// Abundant numbers
//
// Write a program that prints all abundant numbers and their abundance, up to a number entered by the user
void problem_6_main()
{
    problem_6_main(std::cin, std::cout);
}
