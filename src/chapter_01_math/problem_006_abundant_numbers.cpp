#include "problem_006_abundant_numbers.h"
#include "math.h"  // divisors

#include "rtc/console_read.h"  // read_positive_number
#include "rtc/print.h"

#include <iostream>  // cout
#include <numeric>  // accumulate

using namespace rtc::print;


// Abundant numbers
//
// Write a program that prints all abundant numbers and their abundance, up to a number entered by the user
void problem_6_main()
{
    // Read limit
    auto limit{ rtc::console::read_positive_number("Please enter a number (starting from 1): ", 1) };

    // Print abundant numbers up to the limit and their abundance
    std::cout << "Abudant numbers up to " << limit << ", {list of divisors}, (and their abundance):\n";
    for (auto i = 1u; i <= limit; ++i)
    {
        auto d = divisors(i);
        auto sum = std::accumulate(d.cbegin(), d.cend(), 0u);
        if (sum > i)
        {
            std::cout << "\t"<< i << " " << d << " (" << sum - i << ")\n";
        }
    }
    std::cout << "\n";
}
