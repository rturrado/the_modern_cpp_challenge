#include "chapter_03_strings_and_regular_expressions/problem_023_binary_to_string_conversion.h"

#include <array>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <numeric>  // iota
#include <ostream>
#include <vector>


// Binary to string conversion
//
// Write a function that, given a range of 8-bit integers (such as an array or vector),
// returns a string that contains a hexadecimal representation of the input data.
// The function should be able to produce both uppercase and lowercase content.
//
// Here are some input and output examples:
// Input: { 0xBA, 0xAD, 0xF0, 0x0D }, output: "BAADF00D" or "baadf00d"
// Input: { 1, 2, 3, 4, 5, 6 }, output: "010203040506"
void problem_23_main(std::ostream& os) {
    using namespace tmcppc::problem_23;

    std::vector<uint8_t> v{ 0xBA, 0xAD, 0xf0, 0x0d };
    fmt::print(os, "Converting vector [{:#02x}] to string \"{}\"\n", fmt::join(v, ", "), to_hex_string(v));

    std::array<uint8_t, 6> a{};
    std::iota(std::begin(a), std::end(a), 1);
    fmt::print(os, "Converting array [{:#02x}] to string \"{}\"\n\n", fmt::join(a, ", "), to_hex_string(a));
}
