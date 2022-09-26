#include "chapter_01_math/problem_003_least_common_multiple.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <stdexcept>  // runtime_error
#include <vector>

using namespace tmcppc::problem_3;


TEST(lcm, empty_v) { EXPECT_THROW(lcm(std::vector<int>{}), std::runtime_error); }
TEST(lcm, zero_element) { EXPECT_THROW(lcm(std::vector<int>{ 10, 0 }), std::runtime_error); }
TEST(lcm, negative_element) { EXPECT_THROW(lcm(std::vector<int>{ -5, 10 }), std::runtime_error); }
TEST(lcm, v_15_50) { EXPECT_EQ(lcm(std::vector<int>{ 15, 50 }), 150); }

TEST(problem_3_main, v_15_50) {
    std::istringstream iss{ "15 50 quit\n" };
    std::ostringstream oss{};
    problem_3_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("The least common multiple of [15, 50] is: 150\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
