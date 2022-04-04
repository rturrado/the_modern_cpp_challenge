#include "chapter_01_math/problem_010_gray_code.h"

#include <bitset>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <ostream>


size_t binary_to_gray(size_t binary)
{
    return binary ^ (binary >> 1);
}


size_t gray_to_binary(size_t gray)
{
    size_t binary{ 0 };
    while (gray != 0) {
        binary ^= gray;
        gray >>= 1;
    }
    return binary;
}


void problem_10_main(std::ostream& os)
{
    fmt::print(os, "Number\tBinary\tGray code\tDecoded Gray code\n");
    for (size_t binary = 0b00000; binary <= 0b11111; ++binary)
    {
        size_t gray{ binary_to_gray(binary) };
        size_t decoded_gray{ gray_to_binary(gray) };
        fmt::print(os, "{}\t{}\t{}\t\t{}\n",
            binary, std::bitset<5>{binary}.to_string(), std::bitset<5>{gray}.to_string(), decoded_gray);
    }
    fmt::print(os, "\n");
}


// Gray code
//
// Write a program that displays the normal binary representations,
// Gray code representations, and decoded Gray code values for all 5-bit numbers
void problem_10_main()
{
    problem_10_main(std::cout);
}
