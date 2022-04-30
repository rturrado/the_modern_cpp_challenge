#include "chapter_07_concurrency/problem_062_parallel_minmax_with_threads.h"
#include "parallel_minmax.h"

#include <ostream>
#include <vector>

void problem_62_main(std::ostream& os) {
    using namespace tmcppc::parallel_minmax::thread;

    parallel_minmax(
        os,
        [](auto first, auto last) { return parallel_min(first, last); },
        [](auto first, auto last) { return parallel_max(first, last); }
    );
}


// Parallel min and max element algorithms using threads
//
// Implement general-purpose parallel algorithms that find the minimum value and, respectively, the maximum value in a given range.
// The parallelism should be implemented using threads, although the number of concurrent threads is an implementation detail.
void problem_62_main() {
    problem_62_main(std::cout);
}
