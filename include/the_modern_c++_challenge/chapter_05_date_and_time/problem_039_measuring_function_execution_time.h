#pragma once

#include <chrono>
#include <functional>  // invoke
#include <ostream>


template <typename Duration, typename F, typename... Args>
Duration measure_time(F&& f, Args&&... args) {
    namespace ch = std::chrono;

    ch::steady_clock::time_point start{ ch::steady_clock::now() };
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    ch::steady_clock::time_point end{ ch::steady_clock::now() };

    return ch::duration_cast<Duration>(end - start);
}


void problem_39_main(std::ostream& os);
void problem_39_main();
