#pragma once

#include <cstdint>
#include <fmt/format.h>
#include <iosfwd>
#include <stdexcept>  // runtime_error
#include <string>
#include <vector>


namespace tmcppc::problem_24 {
    struct from_hex_char_error : public std::runtime_error {
        explicit from_hex_char_error(char c) : std::runtime_error{ fmt::format("'{}' is not a valid hex char", c) } {}
    };

    struct from_hex_string_parse_error : public std::runtime_error {
        explicit from_hex_string_parse_error(const std::string& message) : std::runtime_error{ message } {}
    };

    // Char to uint8_t
    uint8_t from_hex_char(char c);

    // Two chars to uint8_t
    uint8_t from_hex_chars(char c1, char c2);

    // String of hexadecimal characters to vector of uint8_t's
    std::vector<uint8_t> from_hex_string(std::string s);

    // String of hexadecimal characters, separated by a given string delimiter, to vector of uint8_t's
    std::vector<uint8_t> from_hex_string(std::string s, const std::string& delimiter);
}  // namespace tmcppc::problem_24


void problem_24_main(std::ostream& os);
void problem_24_main();
