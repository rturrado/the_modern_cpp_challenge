#include "problem_013_computing_the_value_of_pi.h"

#include <iostream>  // cout
#include <random>


double compute_pi(size_t number_of_iterations)
{
    using my_engine = std::default_random_engine;  // type of engine
    using my_distribution = std::uniform_real_distribution<>;  // type of distribution

    my_engine re{};  // the default engine
    my_distribution dist{ 0, 1 };  // distribution that maps to the doubles 0.0 to 1.0

    auto die = [&]() { return dist(re); };  // make a generator

    size_t dots_within_circle_count{ 0 };
    size_t dots_within_square_count{ 0 };
    for (size_t i = 0; i < number_of_iterations; ++i)
    {
        double x = die();  // roll the die: x becomes a value in [0.0:1.0]
        double y = die();  // roll the die: x becomes a value in [0.0:1.0]

        if (x * x + y * y <= 1)
        {
            dots_within_circle_count++;
        }
        dots_within_square_count++;
    }

    return (4.0 * dots_within_circle_count) / dots_within_square_count;
}


// Computing the value of Pi
//
// Write a program that computes the value of Pi with a precision of two decimal digits
void problem_13_main()
{
    for (size_t number_of_iterations : {10, 100, 1'000, 10'000, 100'000, 1'000'000, 10'000'000 })
    {
        std::cout << "Estimated value of pi: " << compute_pi(number_of_iterations) << "\n";
    }
    std::cout << "\n";
}
