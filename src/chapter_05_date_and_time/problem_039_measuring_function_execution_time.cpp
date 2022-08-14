#include "chapter_05_date_and_time/problem_039_measuring_function_execution_time.h"

#include <algorithm>  // shuffle, sort
#include <cassert>  // assert
#include <chrono>
#include <iostream>  // cout
#include <fmt/chrono.h>
#include <fmt/ostream.h>
#include <numeric>  // iota
#include <random>  // mt19937, random_device
#include <utility>  // forward, pair
#include <vector>


namespace tmcppc::problem_39 {
    void sort_vector(std::vector<int>& v) {
        std::ranges::sort(v);
        assert(v[0] == 1);
    };

    void sort_iota_vector(size_t num_elems, size_t num_reps) {
        assert(num_elems > 0);
        std::vector<int> v(num_elems);
        std::iota(begin(v), end(v), 1);
        while (num_reps-- != 0) {
            auto w{ v };
            sort_vector(w);
        }
    }

    void sort_shuffle_vector(size_t num_elems, size_t num_reps) {
        assert(num_elems > 0);
        std::vector<int> v(num_elems);
        std::iota(begin(v), end(v), 1);
        std::ranges::shuffle(v, std::mt19937{ std::random_device{}() });
        while (num_reps-- != 0) {
            auto w{ v };
            sort_vector(w);
        }
    }
}  // namespace tmcppc::problem_39


void problem_39_main(std::ostream& os) {
    namespace ch = std::chrono;
    using namespace tmcppc::problem_39;

    fmt::print(os, "Measuring times...\n");
    using vector_of_elems_and_reps = std::vector<std::pair<size_t, size_t>>;
    for (const auto& [num_elems, num_reps] : vector_of_elems_and_reps{ {1'000'000, 1}, {1000, 1000} }) {
        auto duration_1{ measure_time<ch::milliseconds>(sort_iota_vector, num_elems, num_reps) };
        auto duration_2{ measure_time<ch::milliseconds>(sort_shuffle_vector, num_elems, num_reps) };

        fmt::print(os, "\tsort_iota_vector(num_elems = {}, num_reps = {}): {}\n", num_elems, num_reps, duration_1);
        fmt::print(os, "\tsort_shuffle_vector(num_elems = {}, num_reps = {}): {}\n\n", num_elems, num_reps, duration_2);
    }
}


// Measuring function execution time
//
// Write a function that can measure the execution time of a function (with any number of arguments)
// in any required duration (such as seconds, milliseconds, microseconds, and so on).
void problem_39_main() {
    problem_39_main(std::cout);
}
