#include "problem_004_largest_prime_smaller_than_given_number.h"
#include "math.h"  // is_prime

#include "rtc/console_read.h"  // read_positive_number

#include <iostream>  // cout


size_t biggest_prime_smaller_than(const size_t n)
{
    return (is_prime(n - 1) ? n - 1 : biggest_prime_smaller_than(n - 1));
};


// Largest prime smaller than given number
//
// Write a program that computes and prints the largest prime number
// that is smaller than a number provided by the user, which must be a positive integer
void problem_4_main()
{
    // Read limit
    auto limit{ rtc::console::read_positive_number("Please enter a number (starting from 2): ", 2) };

    // Calculate biggest prime smaller than limit
    std::cout << "Biggest prime number smaller than " << limit << " is: " << biggest_prime_smaller_than(limit) << "\n\n";
}
