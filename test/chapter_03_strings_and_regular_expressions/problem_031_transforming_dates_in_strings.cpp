#include "chapter_03_strings_and_regular_expressions/problem_031_transforming_dates_in_strings.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


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
        "\tError: invalid date format: \"1/1/1980\"\n"
    ));
}
