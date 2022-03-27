#include "chapter_01_math/problem_011_converting_numerical_values_to_roman.h"
#include "rtc/console_read.h"  // read_positive_number
#include "rtc/print.h"
#include "rtc/timer.h"  // function_timer

#include <cassert>  // assert
#include <chrono>  // duration, milli
#include <iostream>  // cin, cout
#include <istream>
#include <map>
#include <ostream>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>  // pair
#include <vector>


constinit const size_t maxRomanNumeral{ 3999 };
constinit const size_t maxToRomanVersion{ 4 };  // number of implementations of to_roman function


enum class DigitPosition
{
    Units,
    Tens,
    Hundreds,
    Thousands
};


// v1: one different function for each digit position
namespace P11_V1
{
    std::string thousands_to_roman(size_t n)
    {
        switch (n)
        {
        case 0: return "";
        case 1: return "M";
        case 2: return "MM";
        case 3: return "MMM";
        default: assert(0 <= n && n <= 3); return "";
        }
    }

    std::string hundreds_to_roman(size_t n)
    {
        switch (n)
        {
        case 0: return "";
        case 1: return "C";
        case 2: return "CC";
        case 3: return "CCC";
        case 4: return "CD";
        case 5: return "D";
        case 6: return "DC";
        case 7: return "DCC";
        case 8: return "DCCC";
        case 9: return "CM";
        default: assert(0 <= n && n <= 9); return "";
        }
    }

    std::string tens_to_roman(size_t n)
    {
        switch (n)
        {
        case 0: return "";
        case 1: return "X";
        case 2: return "XX";
        case 3: return "XXX";
        case 4: return "XL";
        case 5: return "L";
        case 6: return "LX";
        case 7: return "LXX";
        case 8: return "LXXX";
        case 9: return "XC";
        default: assert(0 <= n && n <= 9); return "";
        }
    }

    std::string units_to_roman(size_t n)
    {
        switch (n)
        {
        case 0: return "";
        case 1: return "I";
        case 2: return "II";
        case 3: return "III";
        case 4: return "IV";
        case 5: return "V";
        case 6: return "VI";
        case 7: return "VII";
        case 8: return "VIII";
        case 9: return "IX";
        default: assert(0 <= n && n <= 9); return "";
        }
    }
}


// v2: one function for all digit positions
// We use a map for knowing what 3 possible letters are used for each digit position
// We use a tuple for getting the letter that means one unit, five units, and ten units for each digit position
namespace P11_V2
{
    std::map<DigitPosition, std::tuple<char, char, char>> romanLettersForDigitPosition {
        {DigitPosition::Thousands, {'M', ' ', ' '}},
        {DigitPosition::Hundreds, {'C', 'D', 'M'}},
        {DigitPosition::Tens, {'X', 'L', 'C'}},
        {DigitPosition::Units, {'I', 'V', 'X'}},
    };

    std::string to_roman(size_t n, DigitPosition dp)
    {
        std::string one{ get<0>(romanLettersForDigitPosition[dp]) };
        std::string five{ get<1>(romanLettersForDigitPosition[dp]) };
        std::string ten{ get<2>(romanLettersForDigitPosition[dp]) };

        switch (n)
        {
        case 0: return "";
        case 1: return one;
        case 2: return one + one;
        case 3: return one + one + one;
        case 4: return one + five;
        case 5: return five;
        case 6: return five + one;
        case 7: return five + one + one;
        case 8: return five + one + one + one;
        case 9: return one + ten;
        default: assert(0 <= n && n <= 9); return "";
        }
    };
}


// v3: one function for all digit positions
// We use a string_view for knowing what 3 possible letters are used for each digit position
// We use a string_view substring for getting the letter that means one unit, five units, and ten units for each digit position
namespace P11_V3
{
    const std::string_view romanNumeralLetters{ "IVXLCDM  " };
    const std::string_view getRomanLettersForDigitPosition(const DigitPosition& dp)
    {
        size_t pos{ static_cast<size_t>(dp) * 2 };
        size_t count{ 3u };
        return romanNumeralLetters.substr(pos, count);
    }

    std::string to_roman(size_t n, DigitPosition dp)
    {
        std::string one{ getRomanLettersForDigitPosition(dp)[0] };
        std::string five{ getRomanLettersForDigitPosition(dp)[1] };
        std::string ten{ getRomanLettersForDigitPosition(dp)[2] };

        switch (n)
        {
        case 0: return "";
        case 1: return one;
        case 2: return one + one;
        case 3: return one + one + one;
        case 4: return one + five;
        case 5: return five;
        case 6: return five + one;
        case 7: return five + one + one;
        case 8: return five + one + one + one;
        case 9: return one + ten;
        default: assert(0 <= n && n <= 9); return "";
        }
    };
}


// v4: book's version
namespace P11_V4
{
    std::string to_roman(size_t value)
    {
        std::vector<std::pair<size_t, char const*>> roman
        {
            { 1000, "M" }, { 900, "CM" },
            { 500, "D" }, { 400, "CD" },
            { 100, "C" }, { 90, "XC" },
            { 50, "L" }, { 40, "XL" },
            { 10, "X" }, { 9, "IX" },
            { 5, "V" }, { 4, "IV" },
            { 1, "I" }
        };

        std::string result;
        for (auto const& kvp : roman)
        {
            while (value >= kvp.first)
            {
                result += kvp.second;
                value -= kvp.first;
            }
        }

        return result;
    }
}


std::string to_roman(size_t n, size_t version)
{
    if (n > maxRomanNumeral)
    {
        throw std::out_of_range("Trying to convert to Roman numeral a number bigger than " + maxRomanNumeral);
    }
    if (version > maxToRomanVersion)
    {
        throw std::out_of_range("Trying to execute a version of to_roman bigger than " + maxToRomanVersion);
    }

    std::string ret{};

    if (version == 4)
    {
        ret = P11_V4::to_roman(n);
    }
    else
    {
        size_t thousands{ n / 1000 };
        size_t hundreds{ (n % 1000) / 100 };
        size_t tens{ (n % 100) / 10 };
        size_t units{ n % 10 };

        switch (version)
        {
        case 1:
            ret = P11_V1::thousands_to_roman(thousands)
                + P11_V1::hundreds_to_roman(hundreds)
                + P11_V1::tens_to_roman(tens)
                + P11_V1::units_to_roman(units);
            break;
        case 2:
            ret = P11_V2::to_roman(thousands, DigitPosition::Thousands)
                + P11_V2::to_roman(hundreds, DigitPosition::Hundreds)
                + P11_V2::to_roman(tens, DigitPosition::Tens)
                + P11_V2::to_roman(units, DigitPosition::Units);
            break;
        case 3:
            ret = P11_V3::to_roman(thousands, DigitPosition::Thousands)
                + P11_V3::to_roman(hundreds, DigitPosition::Hundreds)
                + P11_V3::to_roman(tens, DigitPosition::Tens)
                + P11_V3::to_roman(units, DigitPosition::Units);
            break;
        default:
            assert(version <= 3); break;
        }
    }

    return ret;
}

namespace P11
{
    void test_function_performance()
    {
        using namespace rtc::timer;

        std::cout << "Test function performance:\n";
        auto t1 = function_timer<>::duration(
            []() {
                for (int i = 0; i < 10000; ++i)
                {
                    for (size_t j : { 99, 999, 1999 })
                    {
                        to_roman(j, 1);
                    }                    
                }
            });
        std::cout << "\tv1: " << std::chrono::duration<double, std::milli>(t1).count() << " ms" << std::endl;

        auto t2 = function_timer<>::duration(
            []() {
                for (int i = 0; i < 10000; ++i)
                {
                    for (size_t j : { 99, 999, 1999 })
                    {
                        to_roman(j, 2);
                    }
                }
            });
        std::cout << "\tv2: " << std::chrono::duration<double, std::milli>(t2).count() << " ms" << std::endl;

        auto t3 = function_timer<>::duration(
            []() {
                for (int i = 0; i < 10000; ++i)
                {
                    for (size_t j : { 99, 999, 1999 })
                    {
                        to_roman(j, 3);
                    }
                }
            });
        std::cout << "\tv3: " << std::chrono::duration<double, std::milli>(t3).count() << " ms" << std::endl;

        auto t4 = function_timer<>::duration(
            []() {
                for (int i = 0; i < 10000; ++i)
                {
                    for (size_t j : { 99, 999, 1999 })
                    {
                        to_roman(j, 4);
                    }
                }
            });
        std::cout << "\tv4: " << std::chrono::duration<double, std::milli>(t4).count() << " ms" << std::endl;
    }
}


void problem_11_main(std::istream& is, std::ostream& os)
{
    // Read a positive number
    auto n{ rtc::console::read_positive_number(is, os, "Please enter a number (between 0 and 3999): ", 0, 4000) };

    // Print the prime factors of that number
    os << "Number\tRoman numeral equivalent\n";
    os << n << "\t" << to_roman(n, 1) << "\n";

    //P11::test_function_performance();

    os << "\n";
}


// Converting numerical values to Roman
//
// Write a program that, given a number entered by the user, prints its Roman numeral equivalent
void problem_11_main()
{
    problem_11_main(std::cin, std::cout);
}
