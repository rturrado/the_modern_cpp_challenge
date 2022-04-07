#include "chapter_03_strings_and_regular_expressions/problem_029_license_plate_validation.h"
#include "rtc/print.h"

#include <ios>  // boolalpha
#include <iostream>  // cout
#include <regex>  // regex_match, sregex_iterator
#include <string>
#include <vector>

using namespace rtc::print;


const std::regex pattern{ R"([[:upper:]]{3}-[[:upper:]]{2} [[:digit:]]{3,4})" };


bool validate_license_plate(const std::string& s)
{
    return std::regex_match(s, pattern);
}


std::vector<std::string> extract_all_license_plates(const std::string& s)
{
    std::vector<std::string> ret{};
    for (std::sregex_iterator it(cbegin(s), cend(s), pattern); it != std::sregex_iterator{}; ++it)
    {
        ret.push_back((*it)[0]);
    }
    return ret;
}


// License plate validation
//
// Considering license plates with the format "LLL-LL DDD" or "LLL-LL DDDD"
// (where L is an uppercase letter from A to Z and D is a digit), write:
//
// - One function that validates that a license plate number is of the correct format
// - One function that, given an input text, extracts and returns all the license plate numbers found in the text
void problem_29_main()
{
    const std::string text{ "AAA-AA 123qwe-ty 1234 ABC-DE 123456..XYZ-WW 0001" };

    // Test validate_license_plate
    const std::string s1{ text.substr(0, 10) };
    const std::string s2{ text.substr(0, 9) };
    const std::string s3{ "ABC-DE 1234" };
    for (const auto& s : { s1, s2, s3 })
    {
        std::cout << "Is \"" << s << "\" a valid license plate?: " << std::boolalpha << validate_license_plate(s) << "\n";
    }

    // Test extract_all_license_plates
    std::cout << "List of valid license plates in \"" << text << "\": " << extract_all_license_plates(text) << "\n";

    std::cout << "\n";
}
