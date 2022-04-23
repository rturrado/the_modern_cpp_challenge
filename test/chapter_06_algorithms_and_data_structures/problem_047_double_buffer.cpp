#include "chapter_06_algorithms_and_data_structures/problem_047_double_buffer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_47_main, output) {
    std::ostringstream oss{};
    problem_47_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Test 1:\n"
        "\t\\(thread 1 writing\\).*\\(thread 2 reading\\).*\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Test 2:\n"
        "\t[ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9]\n"
        "\t[10, 11, 12, 13, 14, 15, 16, 17, 18, 19]\n"
        "\t[30, 31, 32, 33, 34, 35, 36, 37, 38, 39]\n"
        "\t[40, 41, 42, 43, 44, 45, 46, 47, 48, 49]\n"
        "\t[60, 61, 62, 63, 64, 65, 66, 67, 68, 69]\n"
        "\t[70, 71, 72, 73, 74, 75, 76, 77, 78, 79]\n"
        "\t[90, 91, 92, 93, 94, 95, 96, 97, 98, 99]\n"
        "\t[90, 91, 92, 93, 94, 95, 96, 97, 98, 99]\n"
        "\t[90, 91, 92, 93, 94, 95, 96, 97, 98, 99]\n"
        "\t[90, 91, 92, 93, 94, 95, 96, 97, 98, 99]\n"
    ));
}

