#include "chapter_06_algorithms_and_data_structures/problem_054_pairwise_algorithm.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <numeric>  // adjacent_difference
#include <vector>


void problem_54_main(std::ostream& os) {
    using namespace tmcppc::problem_54;

    std::vector v_1(6, 1);
    std::vector v_2(7, 1);  // v_2 has an odd number of elements

    // Fill vectors with the Fibonacci sequence
    std::adjacent_difference(begin(v_1), prev(end(v_1)), next(begin(v_1)), std::plus<>{});
    std::adjacent_difference(begin(v_2), prev(end(v_2)), next(begin(v_2)), std::plus<>{});

    fmt::print(os, "Zipping {} with next: {}\n", v_1, zip_with_next(std::as_const(v_1)));
    fmt::print(os, "Zipping {} with next: {}\n\n", v_2, zip_with_next(std::as_const(v_1)));
}


// Pairwise algorithm
//
// Write a general-purpose function that, given a range, returns a new range with pairs of consecutive elements from the input range.
// Should the input range have an odd number of elements, the last one must be ignored.
// For example, if the input range was { 1, 1, 3, 5, 8, 13, 21 }, the result must be { { 1, 1 }, { 3, 5 }, { 8, 13 } }.
void problem_54_main() {
    problem_54_main(std::cout);
}
