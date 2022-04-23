#include "chapter_01_math/problem_007_amicable_numbers.h"
#include "chapter_01_math/math.h"  // amicable, divisors_sum

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <ostream>
#include <utility>  // pair
#include <vector>


std::vector<std::pair<size_t, size_t>> amicable_numbers_up_to(size_t limit) {
    using namespace tmcppc::math;

    std::vector<std::pair<size_t, size_t>> ret{};

    for (size_t i{ 1 }; i < limit; ++i) {
        auto j{ divisors_sum(i) };
        // Both pairs of amicable numbers have to be smaller than limit
        // And we only print (i, j) pairs where i < j
        auto k{ (j < limit and i < j) ? divisors_sum(j) : 0 };

        if (i == k) {
            ret.push_back({ i, j });
        }
    }

    return ret;
}


void problem_7_main(std::ostream& os) {
    const size_t limit{ 1'000'000 };
    fmt::print(os, "Amicable numbers up to {}:\n", limit);
    for (auto&& p : amicable_numbers_up_to(limit)) {
        fmt::print(os, "\t{}\n", p);
    }
    fmt::print(os, "\n");
}


// Amicable numbers
//
// Write a program that prints the list of all pairs of amicable numbers smaller than 1,000,000
void problem_7_main() {
    problem_7_main(std::cout);
}


void playing_with_tmp(std::ostream& os) {
    using namespace tmcppc::math::tmp;

    fmt::print(os, "Divisors sum of 220: {}\n", divisors_sum<220>::value);
    // fatal error C1202: recursive type or function dependency context too complex
    // fmt::print("Divisors sum of 898216: {}\n", divisors_sum<898216>::value);
    if (amicable<220>::has_amicable) {
        fmt::print(os, "Amicable number of 220: {}\n", amicable<220>::value);
        // fatal error C1202: recursive type or function dependency context too complex
        // fmt::print(os, "Amicable number of 898216: {}\n", amicable<898216>::value);
    }
}


void playing_with_tmp() {
    playing_with_tmp(std::cout);
}
