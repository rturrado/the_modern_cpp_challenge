#pragma once

#include <chrono>
#include <functional>  // invoke
#include <iosfwd>
#include <vector>


namespace tmcppc::problem_39 {
    void sort_vector(std::vector<int>& v);
    void sort_iota_vector(size_t num_elems, size_t num_reps);
    void sort_shuffle_vector(size_t num_elems, size_t num_reps);

    template <typename Duration, typename F, typename... Args>
    Duration measure_time(F&& f, Args&&... args) {
        namespace ch = std::chrono;

        ch::steady_clock::time_point start{ ch::steady_clock::now() };
        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        ch::steady_clock::time_point end{ ch::steady_clock::now() };

        return ch::duration_cast<Duration>(end - start);
    }
}  // namespace tmcppc::problem_39


void problem_39_main(std::ostream& os);
