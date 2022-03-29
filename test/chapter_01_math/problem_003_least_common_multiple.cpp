#include "chapter_01_math/problem_003_least_common_multiple.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>
#include <sstream>  // istringstream, ostringstream
#include <vector>


TEST(lcm, empty_v) {
    std::vector<int> v{};
    EXPECT_EQ(lcm(v), -1);
}

TEST(lcm, zero_element) {
    std::vector<int> v{ 10, 0 };
    EXPECT_EQ(lcm(v), 10);
}

TEST(lcm, negative_element) {
    std::vector<int> v{ -5, 10 };
    EXPECT_EQ(lcm(v), 10);
}

TEST(lcm, fifteen_and_fifty) {
    std::vector<int> v{ 15, 50 };
    EXPECT_EQ(lcm(v), 150);
}

TEST(problem_3_main, fifteen_and_fifty) {
    std::istringstream iss{ "15 50 quit\n" };
    std::ostringstream oss{};
    problem_3_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("The least common multiple of [15, 50] is: 150"));
}
