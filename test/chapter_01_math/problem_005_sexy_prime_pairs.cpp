#include "chapter_01_math/problem_005_sexy_prime_pairs.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream
#include <utility>  // pair
#include <vector>


TEST(sexy_prime_pairs_up_to, DISABLED_zero) {
    std::vector<std::pair<size_t, size_t>> result{};
    EXPECT_EQ(sexy_prime_pairs_up_to(0), result);
}
TEST(sexy_prime_pairs_up_to, DISABLED_one) {
    std::vector<std::pair<size_t, size_t>> result{};
    EXPECT_EQ(sexy_prime_pairs_up_to(1), result);
}
TEST(sexy_prime_pairs_up_to, DISABLED_two) {
    std::vector<std::pair<size_t, size_t>> result{};
    EXPECT_EQ(sexy_prime_pairs_up_to(2), result);
}
TEST(sexy_prime_pairs_up_to, DISABLED_three) {
    std::vector<std::pair<size_t, size_t>> result{};
    EXPECT_EQ(sexy_prime_pairs_up_to(3), result);
}
TEST(sexy_prime_pairs_up_to, DISABLED_four) {
    std::vector<std::pair<size_t, size_t>> result{};
    EXPECT_EQ(sexy_prime_pairs_up_to(4), result);
}
TEST(sexy_prime_pairs_up_to, DISABLED_five) {
    std::vector<std::pair<size_t, size_t>> result{};
    EXPECT_EQ(sexy_prime_pairs_up_to(5), result);
}
TEST(sexy_prime_pairs_up_to, DISABLED_six) {
    std::vector<std::pair<size_t, size_t>> result{};
    EXPECT_EQ(sexy_prime_pairs_up_to(6), result);
}

TEST(sexy_prime_pairs_up_to, DISABLED_seven) {
    EXPECT_THAT(sexy_prime_pairs_up_to(7), ::testing::ElementsAre(::testing::Pair<size_t, size_t>(1, 7)));
}

TEST(sexy_prime_pairs_up_to, DISABLED_forty_eight) {
    EXPECT_THAT(sexy_prime_pairs_up_to(48), ::testing::ElementsAre(
        ::testing::Pair<size_t, size_t>(1, 7),
        ::testing::Pair<size_t, size_t>(5, 11),
        ::testing::Pair<size_t, size_t>(7, 13),
        ::testing::Pair<size_t, size_t>(11, 17),
        ::testing::Pair<size_t, size_t>(13, 19),
        ::testing::Pair<size_t, size_t>(17, 23),
        ::testing::Pair<size_t, size_t>(23, 29),
        ::testing::Pair<size_t, size_t>(31, 37),
        ::testing::Pair<size_t, size_t>(37, 43),
        ::testing::Pair<size_t, size_t>(41, 47)
    ));
}

TEST(program_5_main, DISABLED_seven) {
    std::istringstream iss{ "7\n" };
    std::ostringstream oss{};
    problem_5_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Sexy prime pairs up to 7:\n\t(1, 7)"));
}
