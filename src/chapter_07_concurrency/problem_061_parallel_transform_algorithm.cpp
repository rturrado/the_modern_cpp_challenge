#include "chapter_07_concurrency/problem_061_parallel_transform_algorithm.h"

#include <execution>  // par
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <numeric>  // iota
#include <ostream>


// Parallel transform algorithm
//
// Write a general-purpose algorithm that applies a given unary function to transform the elements of a range in parallel.
// The unary operation used to transform the range must not invalidate range iterators or modify the elements of the range.
// The level of parallelism, that is, the number of execution threads and the way it is achieved, is an implementation detail.
void problem_61_main(std::ostream& os) {
    auto square = [](int n) { return n * n; };

    std::vector<int> v(10);
    std::vector<int> w(10);
    std::iota(std::begin(v), std::end(v), 0);

    fmt::print(os, "v = {}\n\n", v);

    std::ranges::transform(v, std::begin(w), square);
    fmt::print(os, "std::transform(v); v = {}\n", w);

    std::transform(std::execution::par, std::cbegin(v), std::cend(v), std::begin(w), square);
    fmt::print(os, "std::transform(std::execution::par, v); v = {}\n", w);

    tmcppc::algorithm::parallel_transform(std::cbegin(v), std::cend(v), std::begin(w), square);
    fmt::print(os, "parallel_transform(v); v = {}\n\n", w);
}
