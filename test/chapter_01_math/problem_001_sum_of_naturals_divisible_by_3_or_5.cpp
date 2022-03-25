//#include "problem_001_sum_of_naturals_divisible_by_3_or_5.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

std::vector<size_t> naturals_divisible_by_3_or_5_up_to_limit_v1(size_t limit);
std::vector<size_t> naturals_divisible_by_3_or_5_up_to_limit_v2(size_t limit);


TEST(sum_of_naturals_divisible_by_3_and_5, zero_v1) {
    size_t limit{ 0 };
    auto ret{ naturals_divisible_by_3_or_5_up_to_limit_v1(limit) };
    EXPECT_EQ(ret, std::vector<size_t>{ 0 });
}

TEST(sum_of_naturals_divisible_by_3_and_5, zero_v2) {
    size_t limit{ 0 };
    auto ret{ naturals_divisible_by_3_or_5_up_to_limit_v2(limit) };
    EXPECT_EQ(ret, std::vector<size_t>{ 0 });
}

TEST(sum_of_naturals_divisible_by_3_and_5, positive_v1) {
    using ::testing::ElementsAre;

    size_t limit{ 47 };
    auto ret{ naturals_divisible_by_3_or_5_up_to_limit_v1(limit) };
    ASSERT_THAT(ret, ElementsAre(0, 3, 5, 6, 9, 10, 12, 15, 18, 20, 21, 24, 25, 27, 30, 33, 35, 36, 39, 40, 42, 45));
}

TEST(sum_of_naturals_divisible_by_3_and_5, positive_v2) {
    using ::testing::ElementsAre;

    size_t limit{ 47 };
    auto ret{ naturals_divisible_by_3_or_5_up_to_limit_v2(limit) };
    ASSERT_THAT(ret, ElementsAre(0, 3, 5, 6, 9, 10, 12, 15, 18, 20, 21, 24, 25, 27, 30, 33, 35, 36, 39, 40, 42, 45));
}
