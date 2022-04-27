#include "chapter_06_algorithms_and_data_structures/problem_050_filtering_a_list_of_phone_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_50_main, output) {
    std::ostringstream oss{};
    problem_50_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of phone numbers:\n"
        "\t[\"555102030\", \"600111222\", \"798070238\", \"1555607080\", \"34987102030\", \"44798183123\", \"+1555101112\", \"+34985242526\", \"+44223344567\"]\n"
        "\n"
        "Filtering numbers from: US\n"
        "\t[\"1555607080\", \"+1555101112\"]\n"
        "\n"
        "Filtering numbers from: Spain\n"
        "\t[\"34987102030\", \"+34985242526\"]\n"
        "\n"
        "Filtering numbers from: UK\n"
        "\t[\"44798183123\", \"+44223344567\"]\n"
    ));
}

