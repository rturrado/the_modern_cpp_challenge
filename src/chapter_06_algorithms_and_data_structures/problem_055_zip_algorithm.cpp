#include "chapter_06_algorithms_and_data_structures/problem_055_zip_algorithm.h"
#include "rtc/print.h"

#include <algorithm>  // min, transform
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <utility>  // make_pair, pair
#include <vector>

template <typename T, typename U>
using zipped_vector = std::vector<std::pair<T, U>>;

template <typename T, typename U>
auto zip(const std::vector<T>& rng_1, const std::vector<U>& rng_2)
{
    zipped_vector<T, U> ret{};
    auto last_pos{std::min(rng_1.size(), rng_2.size())};
    std::transform(cbegin(rng_1), cbegin(rng_1) + last_pos, cbegin(rng_2), std::back_inserter(ret),
        [](const T& t, const U& u) { return std::make_pair(t, u); });
    return ret;
}

// Zip algorithm
//
// Write a function that, given two ranges, returns a new range with pairs of elements from the two ranges.
// Should the two ranges have different sizes, the result must contain as many elements as the smallest of the input ranges.
// For example, if the input ranges were { 1, 2, 3 , 4, 5, 6, 7, 8, 9, 10 } and { 1, 1, 3, 5, 8, 13, 21 },
// the result should be { { 1, 1 }, { 2, 1 }, { 3, 3 }, { 4, 5 }, { 5, 8 }, { 6, 13 }, {7, 21} }.
void problem_55_main()
{
    const std::vector<int> rng_1{ 1, 2, 3 , 4, 5, 6, 7, 8, 9, 10 };
    const std::vector<int> rng_2{ 1, 1, 3, 5, 8, 13, 21 };
    const std::vector<char> rng_3{ 'a', 'b', 'c', 'd', 'e' };

    std::cout << "Zipping " << rng_1 << " and " << rng_2 << ":\n";
    std::cout << "\t" << zip(rng_1, rng_2) << "\n\n";

    std::cout << "Zipping " << rng_1 << " and " << rng_3 << ":\n";
    std::cout << "\t" << zip(rng_1, rng_3) << "\n\n";
}
