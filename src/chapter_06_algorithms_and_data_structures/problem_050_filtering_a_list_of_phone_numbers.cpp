#include "chapter_06_algorithms_and_data_structures/problem_050_filtering_a_list_of_phone_numbers.h"
#include "chapter_06_algorithms_and_data_structures/phone_numbers.h"

#include <algorithm>  // copy_if
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <ostream>
#include <regex>  // regex_match, smatch
#include <string>  // stoi
#include <vector>

using phone_numbers = tmcppc::phone_numbers;
using country_code = tmcppc::country_code;


phone_numbers filter_phone_numbers_by_country_code(const phone_numbers& ph_nos, const country_code& cc) {
    phone_numbers ret{};
    std::smatch matches{};
    // + is optional, country code should be followed by a 9-digit number
    const std::regex pattern{ R"(^\+?([[:digit:]]+)[[:digit:]]{9}$)" };
    std::copy_if(cbegin(ph_nos), cend(ph_nos), std::back_inserter(ret), [&matches, &pattern, &cc](const auto& ph_no) {
        return (
            std::regex_match(ph_no, matches, pattern) and
            std::stoi(matches[1]) == static_cast<int>(cc)  // matches[1] is country code
        );
    });
    return ret;
}


void problem_50_main(std::ostream& os) {
    const std::vector<std::string> phone_numbers{
        "555102030",
        "600111222",
        "798070238",
        "1555607080",
        "34987102030",
        "44798183123",
        "+1555101112",
        "+34985242526",
        "+44223344567"
    };

    fmt::print(os, "List of phone numbers:\n\t{}\n\n", phone_numbers);

    for (const country_code& cc : { country_code::US, country_code::Spain, country_code::UK }) {
        fmt::print(os, "Filtering numbers from: {}\n\t", cc);
        fmt::print(os, "{}\n\n", filter_phone_numbers_by_country_code(phone_numbers, cc));
    }
}


// Filtering a list of phone numbers
//
// Write a function that, given a list of phone numbers, returns only the numbers that are from a specified country.
// The country is indicated by its phone country code, such as 44 for Great Britain.
// Phone numbers may start with the country code, a + followed by the country code, or have no country code.
// The ones from this last category must be ignored.
void problem_50_main() {
    problem_50_main(std::cout);
}
