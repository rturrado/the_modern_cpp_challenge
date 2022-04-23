#include "chapter_02_language_features/problem_020_contains_any_all_or_none_from_a_range.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_20_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_20_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Checking std::vector<int> v{ 1, 2, 3, 4, 5, 6 } contains_any of (0, 3, 30)\n"
        "Checking std::array<int, 6> a{ 1, 2, 3, 4, 5, 6 } contains_all of (1, 3, 5, 6)\n"
        "Checking std::list<int> l{ 1, 2, 3, 4, 5, 6 } not contains_none of (0, 6)\n"
    ));
}
