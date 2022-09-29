#pragma once

#include <fmt/core.h>
#include <map>
#include <stdexcept>  // out_of_range
#include <string>
#include <string_view>
#include <tuple>
#include <utility>  // pair
#include <vector>

#undef NDEBUG
#include <cassert>  // assert


namespace tmcppc::date {
    constinit const size_t max_roman_numeral{ 3999 };

    enum class digit_position { units, tens, hundreds, thousands };


    // v1: one different function for each digit position
    //
    inline std::string thousands_to_roman(size_t n) {
        switch (n) {
            case 0: return "";
            case 1: return "M";
            case 2: return "MM";
            case 3: return "MMM";
            default:
                assert(0 <= n && n <= 3);
                return "";
        }
    }

    inline std::string hundreds_to_roman(size_t n) {
        switch (n) {
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
            default:
                assert(0 <= n && n <= 9);
                return "";
        }
    }

    inline std::string tens_to_roman(size_t n) {
        switch (n) {
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
            default:
                assert(0 <= n && n <= 9);
                return "";
        }
    }

    inline std::string units_to_roman(size_t n) {
        switch (n) {
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
            default:
                assert(0 <= n && n <= 9);
                return "";
        }
    }

    inline std::string to_roman_v1(size_t n) {
        if (n == 0 or n > max_roman_numeral) {
            auto error_message{ fmt::format("Error: number is out of the Roman numeral range [1, {}].", max_roman_numeral) };
            throw std::out_of_range(error_message.c_str());
        }

        size_t thousands{ n / 1000 };
        size_t hundreds{ (n % 1000) / 100 };
        size_t tens{ (n % 100) / 10 };
        size_t units{ n % 10 };

        return thousands_to_roman(thousands)
            + hundreds_to_roman(hundreds)
            + tens_to_roman(tens)
            + units_to_roman(units);
    }


    // v2: one function for all digit positions
    //
    // We use a map for knowing what 3 possible letters are used for each digit position
    // We use a tuple for getting the letter that means one unit, five units, and ten units for each digit position
    inline std::string to_roman_v2(size_t n, digit_position dp) {
        static const std::map<digit_position, std::tuple<char, char, char>> roman_letters_for_digit_position{
            { digit_position::thousands, { 'M', ' ', ' ' } },
            { digit_position::hundreds, { 'C', 'D', 'M' } },
            { digit_position::tens, { 'X', 'L', 'C' } },
            { digit_position::units, { 'I', 'V', 'X' } },
        };

        std::string one{ get<0>(roman_letters_for_digit_position.at(dp)) };
        std::string five{ get<1>(roman_letters_for_digit_position.at(dp)) };
        std::string ten{ get<2>(roman_letters_for_digit_position.at(dp)) };

        switch (n) {
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
            default:
                assert(0 <= n && n <= 9);
                return "";
        }
    };

    inline std::string to_roman_v2(size_t n) {
        if (n == 0 or n > max_roman_numeral) {
            auto error_message{ fmt::format("number is out of the Roman numeral range [1, {}].", max_roman_numeral) };
            throw std::out_of_range(error_message.c_str());
        }

        size_t thousands{ n / 1000 };
        size_t hundreds{ (n % 1000) / 100 };
        size_t tens{ (n % 100) / 10 };
        size_t units{ n % 10 };

        return to_roman_v2(thousands, digit_position::thousands)
            + to_roman_v2(hundreds, digit_position::hundreds)
            + to_roman_v2(tens, digit_position::tens)
            + to_roman_v2(units, digit_position::units);
    }


    // v3: one function for all digit positions
    //
    // We use a string_view for knowing what 3 possible letters are used for each digit position
    // We use a string_view substring for getting the letter that means one unit, five units, and ten units for each digit position
    inline std::string_view get_roman_letters_for_digit_position(const digit_position& dp) {
        static std::string_view roman_numeral_letters{ "IVXLCDM  " };

        size_t pos{ static_cast<size_t>(dp) * 2 };
        size_t count{ 3u };
        return roman_numeral_letters.substr(pos, count);
    }

    inline std::string to_roman(size_t n, digit_position dp) {
        std::string one{ get_roman_letters_for_digit_position(dp)[0] };
        std::string five{ get_roman_letters_for_digit_position(dp)[1] };
        std::string ten{ get_roman_letters_for_digit_position(dp)[2] };

        switch (n) {
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
            default:
                assert(0 <= n && n <= 9);
                return "";
        }
    };

    inline std::string to_roman_v3(size_t n) {
        if (n == 0 or n > max_roman_numeral) {
            auto error_message{ fmt::format("number is out of the Roman numeral range [1, {}].", max_roman_numeral) };
            throw std::out_of_range(error_message.c_str());
        }

        size_t thousands{ n / 1000 };
        size_t hundreds{ (n % 1000) / 100 };
        size_t tens{ (n % 100) / 10 };
        size_t units{ n % 10 };

        return to_roman(thousands, digit_position::thousands)
            + to_roman(hundreds, digit_position::hundreds)
            + to_roman(tens, digit_position::tens)
            + to_roman(units, digit_position::units);
    }


    // v4: book's version
    //
    inline std::string to_roman_v4(size_t n) {
        if (n == 0 or n > max_roman_numeral) {
            auto error_message{ fmt::format("number is out of the Roman numeral range [1, {}].", max_roman_numeral) };
            throw std::out_of_range(error_message.c_str());
        }

        std::vector<std::pair<size_t, const char*>> roman{
            { 1000, "M" }, { 900, "CM" },
            { 500, "D" }, { 400, "CD" },
            { 100, "C" }, { 90, "XC" },
            { 50, "L" }, { 40, "XL" },
            { 10, "X" }, { 9, "IX" },
            { 5, "V" }, { 4, "IV" },
            { 1, "I" }
        };

        std::string ret{};
        for (const auto& kvp : roman) {
            while (n >= kvp.first) {
                ret += kvp.second;
                n -= kvp.first;
            }
        }

        return ret;
    }
}  // namespace tmcppc::date
