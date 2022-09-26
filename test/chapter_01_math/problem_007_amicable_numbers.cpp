#include "chapter_01_math/problem_007_amicable_numbers.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <utility>  // pair
#include <vector>

using namespace tmcppc::problem_7;


TEST(amicable_numbers_up_to, limit_0) {
    std::vector<std::pair<size_t, size_t>> result{};
    EXPECT_EQ(amicable_numbers_up_to(0), result);
}
TEST(amicable_numbers_up_to, limit_250) {
    std::vector<std::pair<size_t, size_t>> result{};
    EXPECT_EQ(amicable_numbers_up_to(0), result);
}
TEST(amicable_numbers_up_to, limit_300) { EXPECT_THAT(amicable_numbers_up_to(300), ::testing::ElementsAre(
    ::testing::Pair(220, 284)));
}

TEST(problem_7_main, limit_1000000) {
    std::ostringstream oss{};
    problem_7_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Amicable numbers up to 1000000:\n"
        "\t(220, 284)\n"
        "\t(1184, 1210)\n"
        "\t(2620, 2924)\n"
        "\t(5020, 5564)\n"
        "\t(6232, 6368)\n"
        "\t(10744, 10856)\n"
        "\t(12285, 14595)\n"
        "\t(17296, 18416)\n"
        "\t(63020, 76084)\n"
        "\t(66928, 66992)\n"
        "\t(67095, 71145)\n"
        "\t(69615, 87633)\n"
        "\t(79750, 88730)\n"
        "\t(100485, 124155)\n"
        "\t(122265, 139815)\n"
        "\t(122368, 123152)\n"
        "\t(141664, 153176)\n"
        "\t(142310, 168730)\n"
        "\t(171856, 176336)\n"
        "\t(176272, 180848)\n"
        "\t(185368, 203432)\n"
        "\t(196724, 202444)\n"
        "\t(280540, 365084)\n"
        "\t(308620, 389924)\n"
        "\t(319550, 430402)\n"
        "\t(356408, 399592)\n"
        "\t(437456, 455344)\n"
        "\t(469028, 486178)\n"
        "\t(503056, 514736)\n"
        "\t(522405, 525915)\n"
        "\t(600392, 669688)\n"
        "\t(609928, 686072)\n"
        "\t(624184, 691256)\n"
        "\t(635624, 712216)\n"
        "\t(643336, 652664)\n"
        "\t(667964, 783556)\n"
        "\t(726104, 796696)\n"
        "\t(802725, 863835)\n"
        "\t(879712, 901424)\n"
        "\t(898216, 980984)\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}

TEST(playing_with_tmp, n_220) {
    std::ostringstream oss{};
    playing_with_tmp(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Divisors sum of 220: 284\n"
        "Amicable number of 220: 284\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
