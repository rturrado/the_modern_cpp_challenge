#include "chapter_06_algorithms_and_data_structures/problem_055_zip_algorithm.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <vector>


// Zip algorithm
//
// Write a function that, given two ranges, returns a new range with pairs of elements from the two ranges.
// Should the two ranges have different sizes, the result must contain as many elements as the smallest of the input ranges.
// For example, if the input ranges were { 1, 2, 3 , 4, 5, 6, 7, 8, 9, 10 } and { 1, 1, 3, 5, 8, 13, 21 },
// the result should be { { 1, 1 }, { 2, 1 }, { 3, 3 }, { 4, 5 }, { 5, 8 }, { 6, 13 }, {7, 21} }.
void problem_55_main(std::ostream& os) {
    using namespace tmcppc::problem_55;

    const std::vector<int> rng_1{ 1, 2, 3 , 4, 5, 6, 7, 8, 9, 10 };
    const std::vector<int> rng_2{ 1, 1, 3, 5, 8, 13, 21 };
    const std::vector<char> rng_3{ 'a', 'b', 'c', 'd', 'e' };

    fmt::print(os, "Zipping {} and {}:\n", rng_1, rng_2);
    fmt::print(os, "\t{}\n\n", zip(rng_1, rng_2));

    fmt::print(os, "Zipping {} and [{}]:\n", rng_1, fmt::join(rng_3, ", "));
    fmt::print(os, "\t{}\n\n", zip(rng_1, rng_3));
}
