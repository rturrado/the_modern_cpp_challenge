#include "Chapter6_AlgorithmsAndDataStructures.h"
#include "RtcPrint.h"

#include <algorithm>  // copy_if
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <ostream>
#include <regex>  // regex_match, smatch
#include <string>  // stoi
#include <vector>

using phone_numbers = std::vector<std::string>;

enum class country_code {
    US = 1,
    Spain = 34,
    UK = 44
};

std::ostream& operator<<(std::ostream& os, const country_code& cc)
{
    switch (cc)
    {
        case country_code::US: os << "US"; break;
        case country_code::Spain: os << "Spain"; break;
        case country_code::UK: os << "UK"; break;
        default: os << "Unknown country code"; break;
    }
    return os;
}

phone_numbers filter_phone_numbers_by_country_code(const phone_numbers& ph_nos, const country_code& cc)
{
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

// Filtering a list of phone numbers
//
// Write a function that, given a list of phone numbers, returns only the numbers that are from a specified country.
// The country is indicated by its phone country code, such as 44 for Great Britain.
// Phone numbers may start with the country code, a + followed by the country code, or have no country code.
// The ones from this last category must be ignored.
void problem_50_main()
{
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

    std::cout << "List of phone numbers:\n\t" << phone_numbers << "\n\n";

    for (const country_code& cc : { country_code::US, country_code::Spain, country_code::UK })
    {
        std::cout << "Filtering numbers from: " << cc << "\n\t";
        std::cout << filter_phone_numbers_by_country_code(phone_numbers, cc) << "\n\n";
    }
}
