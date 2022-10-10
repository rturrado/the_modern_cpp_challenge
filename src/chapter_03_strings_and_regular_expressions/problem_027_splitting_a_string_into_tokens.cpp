#include "chapter_03_strings_and_regular_expressions/problem_027_splitting_a_string_into_tokens.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <string>
#include <vector>


namespace tmcppc::problem_27 {
    std::vector<std::string> split(const std::string& s, const std::string& delimiters) {
        std::vector<std::string> ret{};
        for (size_t previous_pos{ 0 }, pos{ 0 }; pos < s.size(); ) {
            pos = s.find_first_of(delimiters, pos);
            if (pos > previous_pos) {
                ret.push_back(s.substr(previous_pos, pos - previous_pos));
            }
            if (pos != std::string::npos) {
                ++pos;
                previous_pos = pos;
            }
        }
        return ret;
    }
}  // namespace tmcppc::problem_27


// Splitting a string into tokens with a list of possible delimiters
//
// Write a function that, given a string and a list of possible delimiter characters,
// splits the string into tokens separated by any of the delimiters and returns them in a std::vector.
//
// Example: "this,is.a sample!!" with delimiters ",.! ", output: { "this", "is", "a", "sample" }.
void problem_27_main(std::ostream& os) {
    using namespace tmcppc::problem_27;

    const std::string s{ "this,is.a sample!!" };
    const std::string d1{ ",.! " };
    const std::string d2{ "#" };
    fmt::print(os, "Splitting string \"{}\" using any delimiter of \"{}\" into: [{}]\n", s, d1, fmt::join(split(s, d1), ", "));
    fmt::print(os, "Splitting string \"{}\" using any delimiter of \"{}\" into: [{}]\n\n", s, d2, fmt::join(split(s, d2), ", "));
}
