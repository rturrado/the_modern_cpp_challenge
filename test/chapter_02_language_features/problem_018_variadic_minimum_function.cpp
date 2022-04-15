#include "chapter_02_language_features/problem_018_variadic_minimum_function.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_18_main, output) {
    std::ostringstream oss{};
    problem_18_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "minimum(1, 7, -3, 42) = -3\n"
        "minimum(un, lugar, de, la, Mancha) = Mancha\n"
        "minimum(un, lugar, de, la, Mancha) = Mancha\n"
        "\n"
        "compare_with(more_than, 1, 7, -3, 42) = 42\n"
        "compare_with(std::greater, un, lugar, de, la, Mancha) = un\n"
    ));
}
