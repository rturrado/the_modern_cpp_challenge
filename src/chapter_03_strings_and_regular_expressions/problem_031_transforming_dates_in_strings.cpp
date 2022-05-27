#include "chapter_03_strings_and_regular_expressions/problem_031_transforming_dates_in_strings.h"

#include <exception>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <regex>  // regex_match, regex_replace, smatch
#include <sstream>  // ostringstream
#include <string>  // stoi


struct invalid_date_format_error : public std::exception {
    explicit invalid_date_format_error(const std::string& date) noexcept { message_ += "\"" + date + "\""; }
    const char* what() const noexcept { return message_.c_str(); }
private:
    std::string message_{ "invalid date format: "};
};


std::string format_date_v1(const std::string& s) {
    uint16_t year{ 0 };
    uint16_t month{ 0 };
    uint16_t day{ 0 };

    std::smatch matches{};
    const std::regex valid_format_pattern_1{ R"(([[:digit:]]{1,2})\.([[:digit:]]{1,2})\.([[:digit:]]{1,4}))" };
    const std::regex valid_format_pattern_2{ R"(([[:digit:]]{1,2})\-([[:digit:]]{1,2})\-([[:digit:]]{1,4}))" };
    if ((std::regex_match(s, matches, valid_format_pattern_1) or
        std::regex_match(s, matches, valid_format_pattern_2)) and
        matches.size() == 4) {

        day = std::stoi(matches[1].str());
        month = std::stoi(matches[2].str());
        year = std::stoi(matches[3].str());
    } else {
        throw invalid_date_format_error(s);
    }

    return fmt::format("{:04}-{:02}-{:02}", year, month, day);
}

// Book's solution
//
// - Works directly on a string_view
// - Performs a regex match and then writes the matched fields, in different order, directly over the string_view's data
// - If the input string doesn't match the regex pattern, it is returned unmodified
//
// - It doesn't care about different separators being used in the same input date; it even considers '/' as a separator
// - It doesn't pad each output field with '0's either
std::string format_date_v2(std::string_view sv) {
    const std::regex valid_format_pattern{ R"(([[:digit:]]{1,2})[\.|\-|/]([[:digit:]]{1,2})[\.|\-|/]([[:digit:]]{1,4}))" };
    const std::string new_format_pattern{ R"($3-$2-$1)" };
    return std::regex_replace(sv.data(), valid_format_pattern, new_format_pattern);
}


void problem_31_main(std::ostream& os) {
    for (auto& date : { "1-1-1980", "25-12-0", "1-111-1980", "1.1-1980", "1/1/1980" }) {
        fmt::print(os, "Input string: {}\n", date);
        try {
            fmt::print(os, "\tformat_date_v1: {}\n", format_date_v1(date));
            fmt::print(os, "\tformat_date_v2: {}\n", format_date_v2(date));
        } catch (const std::exception& err) {
            fmt::print(os, "\tError: {}\n", err.what());
        }
    }

    fmt::print(os, "\n");
}


// Transforming dates in strings
//
// Write a function that, given a text containing dates in the format dd.mm.yyyy or dd-mm-yyyy,
// transforms the text so that it contains dates in the format yyyy-mm-dd
void problem_31_main() {
    problem_31_main(std::cout);
}
