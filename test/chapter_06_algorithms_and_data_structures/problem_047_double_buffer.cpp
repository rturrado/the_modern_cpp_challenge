#include "chapter_06_algorithms_and_data_structures/problem_047_double_buffer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_47_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_47_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Test 1:\n"
        "\t\\(thread 1 writing\\).*\\(thread 2 reading\\).*\n"
    ));
    // Test 2:\n\(t\[\s*(\d+,\s+){9}\d+\]){10}
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Test 2:\n"
        "\t\\[\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+\\]\n"
        "\t\\[\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+\\]\n"
        "\t\\[\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+\\]\n"
        "\t\\[\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+\\]\n"
        "\t\\[\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+\\]\n"
        "\t\\[\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+\\]\n"
        "\t\\[\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+\\]\n"
        "\t\\[\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+\\]\n"
        "\t\\[\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+\\]\n"
        "\t\\[\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+,\\s+\\d+\\]\n"
    ));
}
