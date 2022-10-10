#pragma once

#include <functional>  // plus
#include <iosfwd>
#include <numeric>  // adjacent_difference
#include <utility>  // as_const, make_pair, pair
#include <vector>


namespace tmcppc::problem_54 {
    template <typename T>
    using pairs_of_consecutive_elements = std::vector<std::pair<T, T>>;

    template <typename T>
    auto zip_with_next(const std::vector<T>& v) {
        pairs_of_consecutive_elements<T> ret{};

        if (v.size() < 2) {
            return ret;
        }

        auto first_cit{ cbegin(v) };
        auto last_cit{ (v.size() % 2 == 0) ? cend(v) : prev(cend(v)) };
        for (auto cit{ first_cit }; cit != last_cit; cit += 2) {
            ret.push_back(std::make_pair(*cit, *(next(cit))));
        }

        return ret;
    }
}  // namespace tmcppc::problem_54


void problem_54_main(std::ostream& os);
