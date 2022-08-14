#include "chapter_03_strings_and_regular_expressions/problem_031_transforming_dates_in_strings.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace tmcppc::problem_31;


TEST(format_date_v1, DISABLED_empty_string) { EXPECT_THROW(format_date_v1(""), invalid_date_format_error); }
TEST(format_date_v1, DISABLED_no_date) { EXPECT_THROW(format_date_v1("More humans than humans"), invalid_date_format_error); }
TEST(format_date_v1, DISABLED_invalid_format_date) { EXPECT_THROW(format_date_v1("155/08/1970"), invalid_date_format_error); }
TEST(format_date_v1, DISABLED_invalid_separator) { EXPECT_THROW(format_date_v1("15/08/1970"), invalid_date_format_error); }
TEST(format_date_v1, DISABLED_valid_format_date) { EXPECT_EQ(format_date_v1("15.08.1970"), "1970-08-15"); }
TEST(format_date_v1, DISABLED_another_valid_format_date) { EXPECT_EQ(format_date_v1("15-08-1970"), "1970-08-15"); }

TEST(format_date_v2, DISABLED_empty_string) { EXPECT_EQ(format_date_v2(""), ""); }
TEST(format_date_v2, DISABLED_no_date) { EXPECT_EQ(format_date_v2("More humans than humans"), "More humans than humans"); }
TEST(format_date_v2, DISABLED_invalid_format_date) { EXPECT_EQ(format_date_v2("155-08-1970"), "11970-08-55"); }
TEST(format_date_v2, DISABLED_invalid_separator) { EXPECT_EQ(format_date_v2("15/08/1970"), "1970-08-15"); }
TEST(format_date_v2, DISABLED_valid_format_date) { EXPECT_EQ(format_date_v2("15.08.1970"), "1970-08-15"); }
TEST(format_date_v2, DISABLED_another_valid_format_date) { EXPECT_EQ(format_date_v2("15-08-1970"), "1970-08-15"); }

TEST(problem_31_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_31_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Input string: 1-1-1980\n"
        "\tformat_date_v1: 1980-01-01\n"
        "\tformat_date_v2: 1980-1-1\n"
        "Input string: 25-12-0\n"
        "\tformat_date_v1: 0000-12-25\n"
        "\tformat_date_v2: 0-12-25\n"
        "Input string: 1-111-1980\n"
        "\tError: invalid date format: \"1-111-1980\"\n"
        "Input string: 1.1-1980\n"
        "\tError: invalid date format: \"1.1-1980\"\n"
        "Input string: 1/1/1980\n"
        "\tError: invalid date format: \"1/1/1980\"\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
