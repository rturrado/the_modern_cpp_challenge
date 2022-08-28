#include "chapter_03_strings_and_regular_expressions/problem_024_string_to_binary_conversion.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace tmcppc::problem_24;


TEST(from_hex_char, hex_number) { EXPECT_EQ(from_hex_char('7'), 7); }
TEST(from_hex_char, uppercase_hex_letter) { EXPECT_EQ(from_hex_char('A'), 10); }
TEST(from_hex_char, lowercase_hex_letter) { EXPECT_EQ(from_hex_char('a'), 10); }
TEST(from_hex_char, uppercase_non_hex_letter) { EXPECT_THROW(from_hex_char('Z'), from_hex_char_error); }
TEST(from_hex_char, lowercase_non_hex_letter) { EXPECT_THROW(from_hex_char('z'), from_hex_char_error); }
TEST(from_hex_char, non_hex_digit) { EXPECT_THROW(from_hex_char('@'), from_hex_char_error); }


TEST(from_hex_chars, two_hex_digits) { EXPECT_EQ(from_hex_chars('7', 'a'), 0x7a); }
TEST(from_hex_chars, one_hex_digit_and_one_non_hex_digit) { EXPECT_THROW(from_hex_chars('7', '@'), from_hex_char_error); }
TEST(from_hex_chars, two_non_hex_digits) { EXPECT_THROW(from_hex_chars('@', '#'), from_hex_char_error); }


TEST(from_hex_string, empty_string) {
    EXPECT_TRUE(from_hex_string("").empty());
}
TEST(from_hex_string, zero_string) {
    EXPECT_THAT(from_hex_string("0"), ::testing::ElementsAre(0));
}
TEST(from_hex_string, valid_string_odd_number_of_digits) {
    EXPECT_THAT(from_hex_string("7af"), ::testing::ElementsAre(0x7, 0xaf));
}
TEST(from_hex_string, valid_string_even_number_of_digits) {
    EXPECT_THAT(from_hex_string("07af"), ::testing::ElementsAre(0x7, 0xaf));
}
TEST(from_hex_string, invalid_string) {
    EXPECT_THROW(from_hex_string("07a@"), from_hex_char_error);
}


TEST(from_hex_string_with_delimiter, empty_string) {
    EXPECT_TRUE(from_hex_string("", "-").empty());
}
TEST(from_hex_string_with_delimiter, zero_string) {
    EXPECT_THAT(from_hex_string("0", "-"), ::testing::ElementsAre(0));
}
TEST(from_hex_string_with_delimiter, valid_string_and_one_char_delimiter) {
    EXPECT_THAT(from_hex_string("07-af", "-"), ::testing::ElementsAre(0x7, 0xaf));
}
TEST(from_hex_string_with_delimiter, valid_string_and_two_chars_delimiter) {
    EXPECT_THAT(from_hex_string("07.-af", ".-"), ::testing::ElementsAre(0x7, 0xaf));
}
TEST(from_hex_string_with_delimiter, non_hex_digit) {
    EXPECT_THROW(from_hex_string("0@-af", "-"), from_hex_char_error);
}
TEST(from_hex_string_with_delimiter, missing_delimiter) {
    EXPECT_THROW(from_hex_string("07a@", "-"), from_hex_string_parse_error);
}
TEST(from_hex_string_with_delimiter, missing_hex_digits) {
    EXPECT_THROW(from_hex_string("0--7--a--f", "-"), from_hex_string_parse_error);
}


TEST(problem_24_main, output) {
    std::ostringstream oss{};
    problem_24_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Converting string \"BAADf00d\" to vector [0xba, 0xad, 0xf0, 0xd]\n"
        "Converting string \"010203040506\" to vector [0x1, 0x2, 0x3, 0x4, 0x5, 0x6]\n"
        "Converting string \"53CC1\" to vector [0x5, 0x3c, 0xc1]\n"
        "Converting string \"00,FF,23,45\" to vector [0x0, 0xff, 0x23, 0x45]\n"
        "Converting string \"1##dd##87\" to vector [0x1, 0xdd, 0x87]\n"
        "Error: parsing string \"1##dd##87\""
    ));
    EXPECT_THAT(oss.str(), ::testing::EndsWith("\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
