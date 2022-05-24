#include "chapter_06_algorithms_and_data_structures/problem_048_most_frequent_element_in_a_range.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_48_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_48_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Most frequent elements in:\n"
        "\t[1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5]\n"
        "\t\t(using v1): [[e=8, c=3], [e=5, c=3]]\n"
        "\t\t(using v2): [(5, 3), (8, 3)]\n"
        "\n"
        "\t[0, a, A, @, 0, A, @, @]\n"
        "\t\t(using v1): [[e=@, c=3]]\n"
        "\t\t(using v2): [('@', 3)]\n"
        "\n"
        "\t[]\n"
        "\t\t(using v1): []\n"
        "\t\t(using v2): []\n"
    ));
}
