#pragma once

#include <algorithm>  // min, transform
#include <iterator>  // back_inserter
#include <ostream>
#include <utility>  // make_pair, pair
#include <vector>


template <typename T, typename U>
using zipped_vector = std::vector<std::pair<T, U>>;

template <typename T, typename U>
auto zip(const std::vector<T>& rng_1, const std::vector<U>& rng_2)
{
    zipped_vector<T, U> ret{};
    auto last_pos{ std::min(rng_1.size(), rng_2.size()) };
    std::transform(cbegin(rng_1), cbegin(rng_1) + last_pos, cbegin(rng_2), std::back_inserter(ret),
        [](const T& t, const U& u) { return std::make_pair(t, u); });
    return ret;
}


void problem_55_main(std::ostream& os);
void problem_55_main();