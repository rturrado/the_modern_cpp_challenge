#include "chapter_08_design_patterns/problem_069_generating_social_security_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>  // all_of
#include <cctype>  // isdigit
#include <chrono>
#include <numeric>  // accumulate
#include <sstream>  // ostringstream
#include <string>  // to_string

using namespace std::chrono_literals;
using namespace tmcppc::ssn;


std::string encode_crc(const std::string& str, int crc_modulo) {
    auto str_sum{ std::accumulate(std::cbegin(str), std::cend(str), 0,
        [pos = static_cast<int>(str.size() + 1)](auto total, unsigned char c) mutable {
            return total + (c - '0') * pos--; }
    )};
    auto check_digit{ crc_modulo - (str_sum % crc_modulo) };
    return (check_digit == crc_modulo)
        ? std::to_string(0)
        : (check_digit >= 10) ? "X" : std::to_string(check_digit);
}


TEST(northeria_ssn_generator, DISABLED_generate_female_1_1_1970) {
    auto result{ northeria_ssn_generator::get_instance().generate(person{ sex::female, 1970y / January / 1 }) };
    EXPECT_TRUE(std::ranges::all_of(result.substr(0, 14), [](unsigned char c) { return std::isdigit(c); }));
    EXPECT_EQ(result[0], '9');
    EXPECT_EQ(result.substr(1, 8), "19700101");
    auto expected_crc{ encode_crc(result.substr(0, 14), 11) };
    auto actual_crc{ result.substr(14, 1) };
    EXPECT_EQ(expected_crc, actual_crc);
}
TEST(northeria_ssn_generator, DISABLED_generate_male_1_1_1970) {
    auto result{ northeria_ssn_generator::get_instance().generate(person{ sex::male, 1970y / January / 1 }) };
    EXPECT_TRUE(std::ranges::all_of(result.substr(0, 14), [](unsigned char c) { return std::isdigit(c); }));
    EXPECT_EQ(result[0], '7');
    EXPECT_EQ(result.substr(1, 8), "19700101");
    auto expected_crc{ encode_crc(result.substr(0, 14), 11) };
    auto actual_crc{ result.substr(14, 1) };
    EXPECT_EQ(expected_crc, actual_crc);
}

TEST(southeria_ssn_generator, DISABLED_generate_female_1_1_1970) {
    auto result{ southeria_ssn_generator::get_instance().generate(person{ sex::female, 2000y / August / 14 }) };
    EXPECT_TRUE(std::ranges::all_of(result, [](unsigned char c) { return std::isdigit(c); }));
    EXPECT_EQ(result[0], '1');
    EXPECT_EQ(result.substr(1, 8), "20000814");
    auto expected_crc{ encode_crc(result.substr(0, 13), 10) };
    auto actual_crc{ result.substr(13, 1) };
    EXPECT_EQ(expected_crc, actual_crc);
}
TEST(southeria_ssn_generator, DISABLED_generate_male_1_1_1970) {
    auto result{ southeria_ssn_generator::get_instance().generate(person{ sex::male, 2000y / August / 14 }) };
    EXPECT_TRUE(std::ranges::all_of(result, [](unsigned char c) { return std::isdigit(c); }));
    EXPECT_EQ(result[0], '2');
    EXPECT_EQ(result.substr(1, 8), "20000814");
    auto expected_crc{ encode_crc(result.substr(0, 13), 10) };
    auto actual_crc{ result.substr(13, 1) };
    EXPECT_EQ(expected_crc, actual_crc);
}


TEST(problem_69_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_69_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "SSNs for \\[Female, 1970/Jan/01\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[Female, 1976/Feb/03\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[Female, 1982/Mar/05\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[Female, 1988/May/08\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[Female, 1994/Jul/11\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[  Male, 2000/Aug/14\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[  Male, 2006/Sep/18\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[  Male, 2012/Oct/22\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[  Male, 2018/Nov/26\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[  Male, 2021/Dec/31\\]: Northerian = ..............., and Southerian = ..............\n"
    ));
}
