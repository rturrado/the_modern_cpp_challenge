#include "chapter_03_strings_and_regular_expressions/problem_024_string_to_binary_conversion.h"

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <ostream>
#include <string>
#include <vector>


namespace tmcppc::problem_24 {
    // Char to uint8_t
    uint8_t from_hex_char(char c) {
        if ('0' <= c and c <= '9') { return static_cast<uint8_t>(c - '0'); }
        else if ('a' <= c and c <= 'f') { return static_cast<uint8_t>(c - 'a' + 10); }
        else if ('A' <= c and c <= 'F') { return static_cast<uint8_t>(c - 'A' + 10); }
        else { throw from_hex_char_error{ c }; }
    }


    // Two chars to uint8_t
    uint8_t from_hex_chars(char c1, char c2) {
        auto top_nibble{ from_hex_char(c1) };
        auto bottom_nibble{ from_hex_char(c2) };
        return static_cast<uint8_t>((top_nibble << 4) + bottom_nibble);
    }


    // String of hexadecimal characters to vector of uint8_t's
    std::vector<uint8_t> from_hex_string(std::string s) {
        if (s.empty()) {
            return std::vector<uint8_t>{};
        }
        if (s.size() % 2 != 0) {
            s = std::string{ "0" } + std::move(s);
        }

        std::vector<uint8_t> ret(s.size() / 2);

        for (size_t i{ 0 }; i < (s.size() / 2); ++i) {
            ret[i] = from_hex_chars(
                s[static_cast<size_t>(i * 2)],
                s[static_cast<size_t>(i * 2 + 1)]);
        }

        return ret;
    }


    // String of hexadecimal characters, separated by a given string delimiter, to vector of uint8_t's
    std::vector<uint8_t> from_hex_string(std::string s, const std::string& delimiter) {
        if (s.empty()) {
            return std::vector<uint8_t>{};
        }
        std::vector<uint8_t> ret{};

        for (size_t pos{ 0 }, previous_pos{ 0 }; ; ) {
            pos = s.find(delimiter, pos);
            auto token{ s.substr(previous_pos, pos - previous_pos) };

            if (token.size() == 1) {
                token = std::string{ "0" } + std::move(token);
            } else if (token.size() != 2) {
                throw from_hex_string_parse_error{
                    fmt::format("parsing string \"{}\". Found token \"{}\" of size '{}' at pos '{}'",
                    s, token, token.size(), previous_pos) };
            }

            ret.push_back(from_hex_chars(token[0], token[1]));

            if (pos == std::string::npos) {
                break;
            } else {
                pos += delimiter.size();
                previous_pos = pos;
            }
        }

        return ret;
    }
}  // namespace tmcppc::problem_24


// String to binary conversion
//
// Write a function that, given a string containing hexadecimal digits as the input argument,
// returns a vector of 8-bit integers that represent the numerical deserialization of the string content.
//
// The following are examples:
// Input: "BAADF00D" or "baadf00d", output: { 0xBA, 0xAD, 0xF0, 0x0D }
// Input: "010203040506", output: { 1, 2, 3, 4, 5, 6 }
void problem_24_main(std::ostream& os) {
    using namespace tmcppc::problem_24;

    try {
        std::string s1{ "BAADf00d" };
        std::string s2{ "010203040506" };
        fmt::print(os, "Converting string \"{}\" to vector [{:#02x}]\n", s1, fmt::join(from_hex_string(s1), ", "));
        fmt::print(os, "Converting string \"{}\" to vector [{:#02x}]\n", s2, fmt::join(from_hex_string(s2), ", "));

        // Input string contains an odd number of characters
        std::string s3{ "53CC1" };
        fmt::print(os, "Converting string \"{}\" to vector [{:#02x}]\n", s3, fmt::join(from_hex_string(s3), ", "));

        // Hexadecimal digits are separated by a delimiter
        std::string s4{ "00,FF,23,45" };
        std::string s5{ "1##dd##87" };
        fmt::print(os, "Converting string \"{}\" to vector [{:#02x}]\n", s4, fmt::join(from_hex_string(s4, ","), ", "));
        fmt::print(os, "Converting string \"{}\" to vector [{:#02x}]\n", s5, fmt::join(from_hex_string(s5, "##"), ", "));

        // Error: delimiter not found
        fmt::print(os, "Converting string \"{}\" to vector [{:#02x}]\n", s5, fmt::join(from_hex_string(s5, ","), ", "));
    } catch (const std::runtime_error& err) {
        fmt::print(os, "Error: {}\n", err.what());
    }
    fmt::print(os, "\n");
}
