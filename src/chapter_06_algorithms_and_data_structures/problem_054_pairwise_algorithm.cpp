#include "chapter_06_algorithms_and_data_structures/problem_054_pairwise_algorithm.h"
#include "rtc/print.h"

#include <functional>  // plus
#include <iostream>  // cout
#include <numeric>  // adjacent_difference
#include <utility>  // as_const, make_pair, pair
#include <vector>

template <typename T>
using pairs_of_consecutive_elements = std::vector<std::pair<T, T>>;

template <typename T>
auto zip_with_next(const std::vector<T>& v)
{
    pairs_of_consecutive_elements<T> ret{};

    if (v.size() < 2) { return ret; }

    auto first_cit{ cbegin(v) };
    auto last_cit{ (v.size() % 2 == 0) ? cend(v) : prev(cend(v)) };
    for (auto cit{ first_cit }; cit != last_cit; cit += 2)
    {
        ret.push_back(std::make_pair(*cit, *(next(cit))));
    }

    return ret;
}

// Pairwise algorithm
//
// Write a general-purpose function that, given a range, returns a new range with pairs of consecutive elements from the input range.
// Should the input range have an odd number of elements, the last one must be ignored.
// For example, if the input range was { 1, 1, 3, 5, 8, 13, 21 }, the result must be { { 1, 1 }, { 3, 5 }, { 8, 13 } }.
void problem_54_main()
{
    std::vector v_1(6, 1);
    std::vector v_2(7, 1);  // v_2 has an odd number of elements

    // Fill vectors with the Fibonacci sequence
    std::adjacent_difference(begin(v_1), prev(end(v_1)), next(begin(v_1)), std::plus<>{});
    std::adjacent_difference(begin(v_2), prev(end(v_2)), next(begin(v_2)), std::plus<>{});

    std::cout << "Zipping " << v_1 << " with next: " << zip_with_next(std::as_const(v_1)) << "\n";
    std::cout << "Zipping " << v_2 << " with next: " << zip_with_next(std::as_const(v_1)) << "\n";

    std::cout << "\n";
}
