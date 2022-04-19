#include "chapter_03_strings_and_regular_expressions/problem_026_joining_strings_with_delimiter.h"

#include <array>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <list>
#include <string>
#include <vector>


void problem_26_main(std::ostream& os) {
    const std::array<std::string, 0> a0{};
    const std::array<std::string, 1> a1{ "Joe" };
    const std::string d3{ "#" };
    fmt::print(os, "Joining [{}] with delimiter \"{}\": {}\n", fmt::join(a0, ", "), d3, join(a0, d3));
    fmt::print(os, "Joining [{}] with delimiter \"{}\": {}\n", fmt::join(a1, ", "), d3, join(a1, d3));

    const std::vector<std::string> v{ "this", "is", "an", "example" };
    const std::string d1{ " " };
    fmt::print(os, "Joining [{}] with delimiter \"{}\": {}\n", fmt::join(v, ", "), d1, join(v, d1));

    const std::list<std::string> l{ "yet", "another", "one!" };
    const std::string d2{ "---" };
    fmt::print(os, "Joining [{}] with delimiter \"{}\": {}\n\n", fmt::join(l, ", "), d2, join(l, d2));
}


// Joining strings together separated by a delimiter
//
// Write a function that, given a list of strings and a delimiter, creates a new string
// by concatenating all the input strings separated with the specified delimiter.
// The delimiter must not appear after the last string, and when no input string is provided,
// the function must return an empty string.
//
// Example: input { "this", "is", "an", "example" } and delimiter ' ' (space), output: "this is an example".
void problem_26_main() {
    problem_26_main(std::cout);
}
