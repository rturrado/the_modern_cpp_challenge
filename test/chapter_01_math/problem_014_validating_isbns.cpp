#include "chapter_01_math/problem_014_validating_isbns.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream

using namespace tmcppc::problem_14;


TEST(read_n_digit_isbn, fewer_digits_than_expected) {
    std::istringstream iss{ "abc\n0123456789\n" };
    std::ostringstream oss{};
    EXPECT_EQ(read_n_digit_isbn(iss, oss, 10), "0123456789");
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input.\n"));
}

TEST(read_n_digit_isbn, more_digits_than_expected) {
    std::istringstream iss{ "012-345-678-901\n0123456789\n" };
    std::ostringstream oss{};
    EXPECT_EQ(read_n_digit_isbn(iss, oss, 10), "0123456789");
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input.\n"));
}

TEST(read_n_digit_isbn, more_characters_than_expected) {
    std::istringstream iss{ "#0123456789\n0123456789\n" };
    std::ostringstream oss{};
    EXPECT_EQ(read_n_digit_isbn(iss, oss, 10), "0123456789");
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input.\n"));
}

TEST(read_n_digit_isbn, valid_input_with_hyphens) {
    std::istringstream iss{ "0-1234-5678-9\n" };
    std::ostringstream oss{};
    EXPECT_EQ(read_n_digit_isbn(iss, oss, 10), "0123456789");
}

TEST(read_n_digit_isbn, valid_input_with_spaces) {
    std::istringstream iss{ "0 1234 5678 9\n" };
    std::ostringstream oss{};
    EXPECT_EQ(read_n_digit_isbn(iss, oss, 10), "0123456789");
}

TEST(read_n_digit_isbn, valid_input_with_hyphens_and_spaces) {
    std::istringstream iss{ "0-12 34-56 78-9\n" };
    std::ostringstream oss{};
    EXPECT_EQ(read_n_digit_isbn(iss, oss, 10), "0123456789");
}


TEST(validate_10_digit_isbn, n_0123456789) { EXPECT_TRUE(validate_10_digit_isbn("0123456789")); }
TEST(validate_10_digit_isbn, n_2123456802) { EXPECT_TRUE(validate_10_digit_isbn("2123456802")); }
TEST(validate_10_digit_isbn, n_0123456780) { EXPECT_FALSE(validate_10_digit_isbn("0123456780")); }
TEST(validate_10_digit_isbn, n_2123456803) { EXPECT_FALSE(validate_10_digit_isbn("2123456803")); }


TEST(validate_13_digit_isbn, n_0123456789012) { EXPECT_TRUE(validate_13_digit_isbn("0123456789012")); }
TEST(validate_13_digit_isbn, n_9782123456803) { EXPECT_TRUE(validate_13_digit_isbn("9782123456803")); }
TEST(validate_13_digit_isbn, n_0123456789013) { EXPECT_FALSE(validate_13_digit_isbn("0123456789013")); }
TEST(validate_13_digit_isbn, n_9782123456804) { EXPECT_FALSE(validate_13_digit_isbn("9782123456804")); }


TEST(problem_14_main, n_0123456789_n_0123456789012) {
    std::istringstream iss{ "0123456789\n0123456780\n0123456789012\n0123456789013\n" };
    std::ostringstream oss{};
    problem_14_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("0123456789 is a valid 10-digit ISBN\n\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("0123456789012 is a valid 13-digit ISBN\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}

TEST(problem_14_main, n_0123456780_n_0123456789013) {
    std::istringstream iss{ "0123456780\n0123456789013\n" };
    std::ostringstream oss{};
    problem_14_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("0123456780 is NOT a valid 10-digit ISBN\n\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("0123456789013 is NOT a valid 13-digit ISBN\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
