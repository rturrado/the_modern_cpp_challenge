#include "chapter_06_algorithms_and_data_structures/problem_055_zip_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_55_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_55_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Zipping [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] and [1, 1, 3, 5, 8, 13, 21]:\n"
        "\t[(1, 1), (2, 1), (3, 3), (4, 5), (5, 8), (6, 13), (7, 21)]\n"
        "\n"
        "Zipping [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] and abcde:\n"
        "\t[(1, 'a'), (2, 'b'), (3, 'c'), (4, 'd'), (5, 'e')]\n"
    ));
}
