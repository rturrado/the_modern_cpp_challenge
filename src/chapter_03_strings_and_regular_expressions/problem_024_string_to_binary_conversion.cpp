#include "chapter_03_strings_and_regular_expressions/problem_024_string_to_binary_conversion.h"
#include "rtc/print.h"

#include <format>
#include <iostream>  // cout
#include <stdexcept>  // runtime_error
#include <string>
#include <vector>

using namespace rtc::print;


// Char to uint8_t
uint8_t to_binary(char c)
{
    uint8_t ret{ 0 };

    if ('0' <= c and c <= '9') { ret = c - '0'; }
    else if ('a' <= c and c <= 'f') { ret = c - 'a' + 10; }
    else if ('A' <= c and c <= 'F') { ret = c - 'A' + 10; }

    return ret;
}


// Two chars to uint8_t
uint8_t to_binary(char c1, char c2)
{
    auto top_nibble{ to_binary(c1) };
    auto bottom_nibble{ to_binary(c2) };
    return static_cast<uint8_t>((top_nibble << 4) + bottom_nibble);
}


// String of hexadecimal characters to vector of uint8_t's
std::vector<uint8_t> to_binary(std::string s)
{
    if (s.size() % 2 != 0)
    {
        s.insert(0, "0");
    }

    std::vector<uint8_t> ret(s.size() / 2);

    for (size_t i{ 0 }; i < (s.size() / 2); ++i)
    {
        ret[i] = to_binary(
            s[static_cast<size_t>(i * 2)],
            s[static_cast<size_t>(i * 2 + 1)]);
    }

    return ret;
}


// String of hexadecimal characters, separated by a given string delimiter, to vector of uint8_t's
std::vector<uint8_t> to_binary(std::string s, const std::string& delimiter)
{
    std::vector<uint8_t> ret{};

    for (size_t pos{ 0 }, previous_pos{ 0 }; pos = s.find(delimiter, pos); )
    {
        auto token{ s.substr(previous_pos, pos - previous_pos) };

        if (token.size() == 1)
        {
            token.insert(0, "0");
        }
        else if (token.size() != 2)
        {
            throw std::runtime_error(
                std::format("parsing string \"{}\". Found token \"{}\" of size '{}' at pos '{}'",
                s, token, token.size(), previous_pos));
        }

        ret.push_back(to_binary(token[0], token[1]));

        if (pos == std::string::npos)
        {
            break;
        }
        else
        {
            pos += delimiter.size();
            previous_pos = pos;
        }
    }

    return ret;
}


// String to binary conversion
//
// Write a function that, given a string containing hexadecimal digits as the input argument,
// returns a vector of 8-bit integers that represent the numerical deserialization of the string content.
//
// The following are examples:
// Input: "BAADF00D" or "baadf00d", output: { 0xBA, 0xAD, 0xF0, 0x0D }
// Input: "010203040506", output: { 1, 2, 3, 4, 5, 6 }
void problem_24_main()
{
    try
    {
        std::string s1{ "BAADf00d" };
        std::string s2{ "010203040506" };
        std::cout << "Converting string \"" << s1 << "\" to vector " << to_binary(s1) << "\n";
        std::cout << "Converting string \"" << s2 << "\" to vector " << to_binary(s2) << "\n";

        // Input string contains an odd number of characters
        std::string s3{ "53CC1" };
        std::cout << "Converting string \"" << s3 << "\" to vector " << to_binary(s3) << "\n";

        // Hexadecimal digits are separated by a delimiter
        std::string s4{ "00,FF,23,45" };
        std::string s5{ "1##dd##87" };
        std::cout << "Converting string \"" << s4 << "\" to vector " << to_binary(s4, ",") << "\n";
        std::cout << "Converting string \"" << s5 << "\" to vector " << to_binary(s5, "##") << "\n";
        std::cout << "Converting string \"" << s5 << "\" to vector " << to_binary(s5, ",") << "\n";
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "Error: " << err.what() << "\n";
    }
    std::cout << "\n";
}
