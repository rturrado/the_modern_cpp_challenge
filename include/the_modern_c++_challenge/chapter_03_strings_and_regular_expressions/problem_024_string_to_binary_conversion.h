#pragma once

#include <cstdint>
#include <iosfwd>
#include <string>
#include <vector>


namespace tmcppc::problem_24 {
    // Char to uint8_t
    uint8_t to_binary(char c);

    // Two chars to uint8_t
    uint8_t to_binary(char c1, char c2);

    // String of hexadecimal characters to vector of uint8_t's
    std::vector<uint8_t> to_binary(std::string s);

    // String of hexadecimal characters, separated by a given string delimiter, to vector of uint8_t's
    std::vector<uint8_t> to_binary(std::string s, const std::string& delimiter);
}  // namespace tmcppc::problem_24


void problem_24_main(std::ostream& os);
void problem_24_main();
