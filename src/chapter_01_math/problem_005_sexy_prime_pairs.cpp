#include "chapter_01_math/problem_005_sexy_prime_pairs.h"
#include "chapter_01_math/math.h"  // is_prime
#include "rtc/console.h"  // read_positive_number

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>
#include <utility>  // pair
#include <vector>


std::vector<std::pair<size_t, size_t>> sexy_prime_pairs_up_to(size_t limit) {
    std::vector<std::pair<size_t, size_t>> ret{};
    for (auto i{ 7 }; i <= limit; ++i) {
        if (tmcppc::math::is_prime(i) and tmcppc::math::is_prime(i - 6)) {
            ret.push_back({ i - 6, i });
        }
    }
    return ret;
}


void problem_5_main(std::istream& is, std::ostream& os) {
    auto limit{ rtc::console::read_positive_number(is, os, "Please enter a number (>= 1): ", 1) };

    fmt::print(os, "Sexy prime pairs up to {}:\n", limit);
    for (auto&& p : sexy_prime_pairs_up_to(limit)) {
        fmt::print(os, "\t{}\n", p);
    }
    fmt::print(os, "\n");
}


// Sexy prime pairs
//
// Write a program that prints all sexy prime pairs up to a limit entered by the user
void problem_5_main() {
    problem_5_main(std::cin, std::cout);
}
