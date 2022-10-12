#include "chapter_01_math/math.h"  // divisors
#include "chapter_01_math/problem_006_abundant_numbers.h"

#include <fmt/ostream.h>
#include <numeric>  // accumulate
#include <rtc/console.h>  // read_positive_number
#include <utility>  // move
#include <vector>


namespace tmcppc::problem_6 {
    std::vector<AbundantNumberResult> abundant_numbers_up_to(size_t limit) {
        std::vector<AbundantNumberResult> ret{};
        for (size_t i{ 1 }; i <= limit; ++i) {
            auto d{ tmcppc::math::divisors(i) };
            auto sum_of_divisors{ std::accumulate(d.cbegin(), d.cend(), static_cast<size_t>(0)) };
            if (sum_of_divisors > i) {
                ret.emplace_back(i, sum_of_divisors - i, std::move(d));
            }
        }
        return ret;
    }
}  // namespace tmcppc::problem_6


// Abundant numbers
//
// Write a program that prints all abundant numbers and their abundance, up to a number entered by the user
void problem_6_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::problem_6;

    auto limit{ rtc::console::read_positive_number(is, os, "Please enter a number (>= 1): ", 1) };

    fmt::print(os, "Abundant numbers up to {} [list of divisors] (and their abundance):\n", limit);
    const auto& results{ abundant_numbers_up_to(static_cast<size_t>(limit)) };
    if (results.empty()) {
        fmt::print(os, "\t[]\n");
    } else {
        for (const auto& result : results) {
            fmt::print(os, "\t{} {} ({})\n", result.number, result.divisors, result.abundance);
        }
    }
    fmt::print(os, "\n");
}
