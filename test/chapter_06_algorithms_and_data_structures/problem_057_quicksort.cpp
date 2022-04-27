#include "chapter_06_algorithms_and_data_structures/problem_057_quicksort.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_57_main, output) {
    std::ostringstream oss{};
    problem_57_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Quicksorting zA9!moN9: !99ANmoz\n"
        "Quicksorting [10, 15, 20, 25, 30, 35, 40]: [40, 30, 20, 10, 35, 25, 15]\n"
    ));
}
