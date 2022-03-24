#include "problem_007_amicable_numbers.h"
#include "math.h"  // divisors_sum, TMP

#include <iostream>  // cout

constinit const size_t limit{ 1'000'000 };


void playing_with_TMP()
{
    std::cout << "Playing with TMP:\n";
    std::cout << "\tDivisors sum of 220: " << TMP::divisors_sum<220>::value << "\n";
    // fatal error C1202: recursive type or function dependency context too complex
    // std::cout << "\tDivisors sum of 898216: " << TMP::divisors_sum<898216>::value << "\n";
    if (TMP::amicable<220>::has_amicable)
    {
        std::cout << "\tAmicable number of 220: {" << 220 << ", " << TMP::amicable<220>::value << "}\n";
        // fatal error C1202: recursive type or function dependency context too complex
        // std::cout << "\tAmicable number of 898216: {" << 220 << ", " << TMP::amicable<898216>::value << "}\n";
    }
}


// Amicable numbers
//
// Write a program that prints the list of all pairs of amicable numbers smaller than 1,000,000
void problem_7_main()
{
    for (auto i = 1u; i < limit; ++i)
    {
        auto j{ divisors_sum(i) };
        // Both pairs of amicable numbers have to be smaller than limit
        // And we only print {i, j} pairs where i < j
        auto k{ (j < limit && i < j) ? divisors_sum(j) : 0 };

        if (i == k)
        {
            std::cout << "\t{ " << i << ", " << j << " }\n";
        }
    }

    playing_with_TMP();

    std::cout << "\n";
}
