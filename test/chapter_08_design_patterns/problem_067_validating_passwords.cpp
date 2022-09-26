#include "chapter_08_design_patterns/problem_067_validating_passwords.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream

using namespace tmcppc::password;
using namespace tmcppc::password::validator;
using tmcppc::password::validator::v2::contains_symbol_or_error;
using tmcppc::password::validator::v2::contains_digit_or_error;
using tmcppc::password::validator::v2::contains_lowercase_or_error;
using tmcppc::password::validator::v2::contains_uppercase_or_error;
using tmcppc::password::validator::v2::contains_validator;

TEST(contains_symbol, empty_string) { EXPECT_FALSE(contains_symbol("")); }
TEST(contains_symbol, string_without_symbols) { EXPECT_FALSE(contains_symbol("abcdefABCDEF0123456789")); }
TEST(contains_symbol, string_with_symbols) { EXPECT_TRUE(contains_symbol("abcdefABCDEF0123456789.,;:!?")); }

TEST(contains_digit, empty_string) { EXPECT_FALSE(contains_digit("")); }
TEST(contains_digit, string_without_digits) { EXPECT_FALSE(contains_digit("abcdefABCDEF.,;:!?")); }
TEST(contains_digit, string_with_digits) { EXPECT_TRUE(contains_digit("abcdefABCDEF0123456789.,;:!?")); }

TEST(contains_lowercase, empty_string) { EXPECT_FALSE(contains_lowercase("")); }
TEST(contains_lowercase, string_without_lowercase) { EXPECT_FALSE(contains_lowercase("ABCDEF0123456789.,;:!?")); }
TEST(contains_lowercase, string_with_lowercase) { EXPECT_TRUE(contains_lowercase("abcdefABCDEF0123456789.,;:!?")); }

TEST(contains_uppercase, empty_string) { EXPECT_FALSE(contains_uppercase("")); }
TEST(contains_uppercase, string_without_uppercase) { EXPECT_FALSE(contains_uppercase("abcdef0123456789.,;:!?")); }
TEST(contains_uppercase, string_with_uppercase) { EXPECT_TRUE(contains_uppercase("abcdefABCDEF0123456789.,;:!?")); }


TEST(v1_minimum_length_validator, empty_string_and_zero_minimum_length) {
    EXPECT_FALSE(tmcppc::password::validator::v1::minimum_length_validator{ 0 }.validate(""));
}
TEST(v1_minimum_length_validator, empty_string_and_nonzero_minimum_length) {
    EXPECT_TRUE(tmcppc::password::validator::v1::minimum_length_validator{ 10 }.validate(""));
}

TEST(v1_contains_symbol_validator, empty_string) {
    EXPECT_TRUE(tmcppc::password::validator::v1::contains_symbol_validator.validate(""));
}
TEST(v1_contains_symbol_validator, string_without_symbols) {
    EXPECT_TRUE(tmcppc::password::validator::v1::contains_symbol_validator.validate("abcdefABCDEF0123456789"));
}
TEST(v1_contains_symbol_validator, string_with_symbols) {
    EXPECT_FALSE(tmcppc::password::validator::v1::contains_symbol_validator.validate("abcdefABCDEF0123456789.,;:!?"));
}

TEST(v1_contains_digit_validator, empty_string) {
    EXPECT_TRUE(tmcppc::password::validator::v1::contains_digit_validator.validate(""));
}
TEST(v1_contains_digit_validator, string_without_digits) {
    EXPECT_TRUE(tmcppc::password::validator::v1::contains_digit_validator.validate("abcdefABCDEF.,;:!?"));
}
TEST(v1_contains_digit_validator, string_with_digits) {
    EXPECT_FALSE(tmcppc::password::validator::v1::contains_digit_validator.validate("abcdefABCDEF0123456789.,;:!?"));
}

TEST(v1_contains_lowercase_validator, empty_string) {
    EXPECT_TRUE(tmcppc::password::validator::v1::contains_lowercase_validator.validate(""));
}
TEST(v1_contains_lowercase_validator, string_without_lowercase) {
    EXPECT_TRUE(tmcppc::password::validator::v1::contains_lowercase_validator.validate("ABCDEF0123456789.,;:!?"));
}
TEST(v1_contains_lowercase_validator, string_with_lowercase) {
    EXPECT_FALSE(tmcppc::password::validator::v1::contains_lowercase_validator.validate("abcdefABCDEF0123456789.,;:!?"));
}

TEST(v1_contains_uppercase_validator, empty_string) {
    EXPECT_TRUE(tmcppc::password::validator::v1::contains_uppercase_validator.validate(""));
}
TEST(v1_contains_uppercase_validator, string_without_uppercase) {
    EXPECT_TRUE(tmcppc::password::validator::v1::contains_uppercase_validator.validate("abcdef0123456789.,;:!?"));
}
TEST(v1_contains_uppercase_validator, string_with_uppercase) {
    EXPECT_FALSE(tmcppc::password::validator::v1::contains_uppercase_validator.validate("abcdefABCDEF0123456789.,;:!?"));
}


TEST(v2_minimum_length_validator, empty_string_and_zero_minimum_length) {
    EXPECT_FALSE(tmcppc::password::validator::v2::minimum_length_validator{ 0 }.validate(""));
}
TEST(v2_minimum_length_validator, empty_string_and_nonzero_minimum_length) {
    EXPECT_TRUE(tmcppc::password::validator::v2::minimum_length_validator{ 10 }.validate(""));
}

TEST(v2_contains_symbol_validator, empty_string) {
    EXPECT_TRUE(contains_validator{ contains_symbol_or_error }.validate(""));
}
TEST(v2_contains_symbol_validator, string_without_symbols) {
    EXPECT_TRUE(contains_validator{ contains_symbol_or_error }.validate("abcdefABCDEF0123456789"));
}
TEST(v2_contains_symbol_validator, string_with_symbols) {
    EXPECT_FALSE(contains_validator{ contains_symbol_or_error }.validate("abcdefABCDEF0123456789.,;:!?"));
}

TEST(v2_contains_digit_validator, empty_string) {
    EXPECT_TRUE(contains_validator{ contains_digit_or_error }.validate(""));
}
TEST(v2_contains_digit_validator, string_without_digits) {
    EXPECT_TRUE(contains_validator{ contains_digit_or_error }.validate("abcdefABCDEF.,;:!?"));
}
TEST(v2_contains_digit_validator, string_with_digits) {
    EXPECT_FALSE(contains_validator{ contains_digit_or_error }.validate("abcdefABCDEF0123456789.,;:!?"));
}

TEST(v2_contains_lowercase_validator, empty_string) {
    EXPECT_TRUE(contains_validator{ contains_lowercase_or_error }.validate(""));
}
TEST(v2_contains_lowercase_validator, string_without_lowercase) {
    EXPECT_TRUE(contains_validator{ contains_lowercase_or_error }.validate("ABCDEF0123456789.,;:!?"));
}
TEST(v2_contains_lowercase_validator, string_with_lowercase) {
    EXPECT_FALSE(contains_validator{ contains_lowercase_or_error }.validate("abcdefABCDEF0123456789.,;:!?"));
}

TEST(v2_contains_uppercase_validator, empty_string) {
    EXPECT_TRUE(contains_validator{ contains_uppercase_or_error }.validate(""));
}
TEST(v2_contains_uppercase_validator, string_without_uppercase) {
    EXPECT_TRUE(contains_validator{ contains_uppercase_or_error }.validate("abcdef0123456789.,;:!?"));
}
TEST(v2_contains_uppercase_validator, string_with_uppercase) {
    EXPECT_FALSE(contains_validator{ contains_uppercase_or_error }.validate("abcdefABCDEF0123456789.,;:!?"));
}


TEST(problem_67_main, output) {
    std::ostringstream oss{};
    problem_67_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "v1:\n"
        "\t'hola' is not valid: password length has to be at least 8.\n"
        "\t'holaquetal' is not valid: password has to contain at least one 'symbol'.\n"
        "\t'holaqueta!' is not valid: password has to contain at least one 'digit'.\n"
        "\t'h0laqueta!' is not valid: password has to contain at least one 'uppercase' letter.\n"
        "\t'H0LAQUETA!' is not valid: password has to contain at least one 'lowercase' letter.\n"
        "\t'h0laQueTa!' is a valid password.\n"
        "\n"
        "v2:\n"
        "\t'hola' is not valid: password length has to be at least 8.\n"
        "\t'holaquetal' is not valid: password has to contain at least one 'symbol'.\n"
        "\t'holaqueta!' is not valid: password has to contain at least one 'digit'.\n"
        "\t'h0laqueta!' is not valid: password has to contain at least one 'uppercase'.\n"
        "\t'H0LAQUETA!' is not valid: password has to contain at least one 'lowercase'.\n"
        "\t'h0laQueTa!' is a valid password.\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
