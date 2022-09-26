#include "chapter_01_math/math.h"  // is_prime
#include "chapter_01_math/problem_005_sexy_prime_pairs.h"

#include "rtc/console.h"  // read_positive_number

#include "fmt/ostream.h"

#include <iostream>  // cin, cout
#include <utility>  // pair
#include <vector>


namespace tmcppc::problem_5 {
    std::vector<std::pair<size_t, size_t>> sexy_prime_pairs_up_to(size_t limit) {
        using namespace tmcppc::math;

        std::vector<std::pair<size_t, size_t>> ret{};
        for (size_t i{ 7 }; i <= limit; ++i) {
            if (tmcppc::math::is_prime(i) and tmcppc::math::is_prime(i - 6)) {
                ret.emplace_back(i - 6, i);
            }
        }
        return ret;
    }
}  // namespace tmcppc::problem_5


void problem_5_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::problem_5;

    auto limit{ rtc::console::read_positive_number(is, os, "Please enter a number (>= 1): ", 1) };

    fmt::print(os, "Sexy prime pairs up to {}:\n", limit);
    for (auto&& p : sexy_prime_pairs_up_to(static_cast<size_t>(limit))) {
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
