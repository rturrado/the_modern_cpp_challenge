#include "chapter_01_math/problem_013_computing_the_value_of_pi.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <ostream>
#include <random>


namespace tmcppc::problem_13 {
    double compute_pi(size_t number_of_iterations) {
        if (number_of_iterations == 0) {
            return 0;
        }

        using my_engine = std::default_random_engine;  // type of engine
        using my_distribution = std::uniform_real_distribution<>;  // type of distribution

        my_engine re{};  // the default engine
        my_distribution dist{ 0, 1 };  // distribution that maps to the doubles 0.0 to 1.0

        auto die = [&]() { return dist(re); };  // make a generator

        size_t dots_within_circle_count{ 0 };
        size_t dots_within_square_count{ number_of_iterations };
        for (size_t i{ 0 }; i < number_of_iterations; ++i) {
            double x = die();  // roll the die: x becomes a value in [0.0:1.0]
            double y = die();  // roll the die: x becomes a value in [0.0:1.0]

            if (x * x + y * y <= 1) {
                dots_within_circle_count++;
            }
        }

        return (4.0 * dots_within_circle_count) / dots_within_square_count;
    }
}  // namespace tmcppc::problem_13


void problem_13_main(std::ostream& os) {
    using namespace tmcppc::problem_13;

    for (size_t number_of_iterations : {10, 100, 1'000, 10'000, 100'000, 1'000'000, 10'000'000 }) {
        fmt::print(os, "Estimated value of pi: {}\n", compute_pi(number_of_iterations));
    }
    fmt::print(os, "\n");
}


// Computing the value of Pi
//
// Write a program that computes the value of Pi with a precision of two decimal digits
void problem_13_main() {
    problem_13_main(std::cout);
}
