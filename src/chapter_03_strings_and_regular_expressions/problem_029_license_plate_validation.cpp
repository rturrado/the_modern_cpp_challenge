#include "chapter_03_strings_and_regular_expressions/problem_029_license_plate_validation.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <regex>  // regex_match, sregex_iterator
#include <string>
#include <vector>


namespace tmcppc::problem_29 {
    bool validate_license_plate(const std::string& s) {
        return std::regex_match(s, pattern);
    }


    std::vector<std::string> extract_all_license_plates(const std::string& s) {
        std::vector<std::string> ret{};
        for (std::sregex_iterator it(cbegin(s), cend(s), pattern); it != std::sregex_iterator{}; ++it) {
            ret.push_back((*it)[0]);
        }
        return ret;
    }
}  // namespace tmcppc::problem_29


// License plate validation
//
// Considering license plates with the format "LLL-LL DDD" or "LLL-LL DDDD"
// (where L is an uppercase letter from A to Z and D is a digit), write:
//
// - One function that validates that a license plate number is of the correct format
// - One function that, given an input text, extracts and returns all the license plate numbers found in the text
void problem_29_main(std::ostream& os) {
    using namespace tmcppc::problem_29;

    const std::string text{ "AAA-AA 123qwe-ty 1234 ABC-DE 123456..XYZ-WW 0001" };

    // Test validate_license_plate
    for (auto&& s : { text.substr(0, 9), text.substr(0, 10), std::string{ "ABC-DE 1234" } }) {
        fmt::print(os, "Is \"{}\" a valid license plate?: {}\n", s, validate_license_plate(s));
    }

    // Test extract_all_license_plates
    fmt::print(os, "List of valid license plates in \"{}\":\n\t{}\n\n", text, extract_all_license_plates(text));
}
