#include "chapter_01_math/problem_001_sum_of_naturals_divisible_by_3_or_5.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream
#include <vector>

using namespace tmcppc::problem_1;


TEST(sum_of_naturals_divisible_by_3_and_5, DISABLED_v1_with_number_0) {
    EXPECT_EQ(naturals_divisible_by_3_or_5_up_to_limit_v1(0), std::vector<size_t>{ 0 });
}

TEST(sum_of_naturals_divisible_by_3_and_5, DISABLED_v2_with_number_0) {
    EXPECT_EQ(naturals_divisible_by_3_or_5_up_to_limit_v2(0), std::vector<size_t>{ 0 });
}

TEST(sum_of_naturals_divisible_by_3_and_5, DISABLED_v1_with_number_47) {
    EXPECT_THAT(
        naturals_divisible_by_3_or_5_up_to_limit_v1(47),
        ::testing::ElementsAre(0, 3, 5, 6, 9, 10, 12, 15, 18, 20, 21, 24, 25, 27, 30, 33, 35, 36, 39, 40, 42, 45));
}

TEST(sum_of_naturals_divisible_by_3_and_5, DISABLED_v2_with_number_47) {
    EXPECT_THAT(
        naturals_divisible_by_3_or_5_up_to_limit_v2(47),
        ::testing::ElementsAre(0, 3, 5, 6, 9, 10, 12, 15, 18, 20, 21, 24, 25, 27, 30, 33, 35, 36, 39, 40, 42, 45));
}

TEST(problem_1_main, DISABLED_number_47) {
    std::istringstream iss{ "47\n" };
    std::ostringstream oss{};
    problem_1_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "The sum of all natural numbers divisible by either 3 or 5 and up to 47 is:\n\t"
        "495 [0, 3, 5, 6, 9, 10, 12, 15, 18, 20, 21, 24, 25, 27, 30, 33, 35, 36, 39, 40, 42, 45]\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
