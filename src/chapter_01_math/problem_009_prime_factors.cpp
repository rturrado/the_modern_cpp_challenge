#include "chapter_01_math/math.h"  // prime_factors
#include "chapter_01_math/problem_009_prime_factors.h"

#include <fmt/ostream.h>
#include <rtc/console.h>  // read_positive_number


// Prime factors of a number
//
// Write a program that prints the prime factors of a number entered by the user
void problem_9_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::math;

    auto n{ rtc::console::read_positive_number(is, os, "Please enter a number (>= 0): ", 0) };

    fmt::print(os, "Prime factors of {}: {}\n\n", n, prime_factors(n));
}
