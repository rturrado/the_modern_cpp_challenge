#include "chapter_06_algorithms_and_data_structures/problem_057_quicksort.h"
#include "chapter_07_concurrency/quicksort.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <ostream>


// Sort algorithm
//
// Write a function that, given a pair of random access Input Iterators to define its lower and upper bounds,
// sorts the elements of the range using the quicksort algorithm.
//
// There should be two overloads of the function:
// one that uses operator< to compare the elements of the range and put them in ascending order,
// and one that uses a user-defined binary comparison function for comparing the elements
void problem_57_main(std::ostream& os) {
    std::vector<char> v_c{ 'z', 'A', '9', '!', 'm', 'o', 'N', '9' };
    fmt::print(os, "Quicksorting [{}]: ", fmt::join(v_c, ", "));
    tmcppc::algorithm::quicksort(begin(v_c), end(v_c));
    fmt::print(os, "[{}]\n", fmt::join(v_c, ", "));

    std::vector<int> v_i{ 10, 15, 20, 25, 30, 35, 40 };
    fmt::print(os, "Quicksorting {}: ", v_i);
    tmcppc::algorithm::quicksort(begin(v_i), end(v_i), [](int i, int j) {
        return (i % 10 - i / 10) < (j % 10 - j / 10);
    });
    fmt::print(os, "{}\n\n", v_i);
}
