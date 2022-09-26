#include "chapter_07_concurrency/problem_063_parallel_minmax_with_async.h"
#include "parallel_minmax.h"

#include <iostream>  // cout
#include <ostream>


void problem_63_main(std::ostream& os) {
    parallel_minmax(
        os,
        [](auto&& rng) { return tmcppc::algorithm::async::parallel_min(rng); },
        [](auto&& rng) { return tmcppc::algorithm::async::parallel_max(rng); }
    );
}


// Parallel min and max element algorithms using asynchronous functions
//
// Implement general-purpose parallel algorithms that find the minimum value and, respectively, the maximum value in a given range.
// The parallelism should be implemented using asynchronous functions,
// although the number of concurrent functions is an implementation detail.
void problem_63_main() {
    problem_63_main(std::cout);
}
