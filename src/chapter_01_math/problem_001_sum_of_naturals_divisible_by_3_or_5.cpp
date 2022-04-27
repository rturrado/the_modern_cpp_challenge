#include "chapter_01_math/problem_001_sum_of_naturals_divisible_by_3_or_5.h"
#include "rtc/console.h"  // read_positive_number

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cin, cout
#include <istream>
#include <numeric>  // accumulate
#include <ostream>
#include <range/v3/core.hpp>
#include <range/v3/range/conversion.hpp>  // to
#include <range/v3/view/filter.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/take.hpp>
#include <vector>


std::vector<size_t> naturals_divisible_by_3_or_5_up_to_limit_v1(size_t limit) {
    std::vector<size_t> ret{};
    for (size_t i{0}; i <= limit; ++i) {
        if ((i % 3 == 0) or (i % 5 == 0)) {
            ret.push_back(i);
        }
    }
    return ret;
}


std::vector<size_t> naturals_divisible_by_3_or_5_up_to_limit_v2(size_t limit) {
    return ranges::views::iota(0)
        | ranges::views::take(limit + 1)
        | ranges::views::filter([](auto i) { return (i % 3 == 0) or (i % 5 == 0); })
        | ranges::to<std::vector<size_t>>();
}


void problem_1_main(std::istream& is, std::ostream& os) {
    auto n{ rtc::console::read_positive_number(is, os, "Please enter a number (>= 0): ", 0) };

    for (auto f : { naturals_divisible_by_3_or_5_up_to_limit_v1 , naturals_divisible_by_3_or_5_up_to_limit_v2 }) {
        auto v{ f(n) };

        fmt::print(os, "The sum of all natural numbers divisible by either 3 or 5 and up to {} is:\n\t{} {}\n\n",
            n, std::accumulate(std::cbegin(v), std::cend(v), static_cast<size_t>(0)), v);
    }
}


// Sum of naturals divisible by 3 or 5
//
// Write a program that calculates and prints the sum of all natural numbers divisible by either 3 or 5,
// up to a given limit entered by the user
void problem_1_main() {
    problem_1_main(std::cin, std::cout);
}
