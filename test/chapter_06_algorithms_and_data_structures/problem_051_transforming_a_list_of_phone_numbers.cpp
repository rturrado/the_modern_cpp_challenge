#include "chapter_06_algorithms_and_data_structures/problem_051_transforming_a_list_of_phone_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_51_main, output) {
    std::ostringstream oss{};
    problem_51_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of phone numbers:\n"
        "\t[\"07555 111111\", \"07555222222\", \"+44 7555 333333\", \"44 7555 444444\", \"7555 555555\"]\n"
        "List of UK phone numbers after formatting:\n"
        "\t[\"+447555111111\", \"+447555222222\", \"+447555333333\", \"+447555444444\", \"+447555555555\"]\n"
        "\n"
        "List of phone numbers:\n"
        "\t[\"+1 2345 666666\", \"34 987 7777777\", \"0 12345678\", \"+02 1234567890\"]\n"
        "List of UK phone numbers after formatting:\n"
        "\t[]\n"
    ));
}
