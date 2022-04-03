#include "chapter_01_math/problem_005_sexy_prime_pairs.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream
#include <utility>  // pair
#include <vector>


TEST(sexy_prime_pairs_up_to, zero) { EXPECT_THAT(sexy_prime_pairs_up_to(0), ::testing::IsEmpty()); }
TEST(sexy_prime_pairs_up_to, one) { EXPECT_THAT(sexy_prime_pairs_up_to(1), ::testing::IsEmpty()); }
TEST(sexy_prime_pairs_up_to, two) { EXPECT_THAT(sexy_prime_pairs_up_to(2), ::testing::IsEmpty()); }
TEST(sexy_prime_pairs_up_to, three) { EXPECT_THAT(sexy_prime_pairs_up_to(3), ::testing::IsEmpty()); }
TEST(sexy_prime_pairs_up_to, four) { EXPECT_THAT(sexy_prime_pairs_up_to(4), ::testing::IsEmpty()); }
TEST(sexy_prime_pairs_up_to, five) { EXPECT_THAT(sexy_prime_pairs_up_to(5), ::testing::IsEmpty()); }
TEST(sexy_prime_pairs_up_to, six) { EXPECT_THAT(sexy_prime_pairs_up_to(6), ::testing::IsEmpty()); }

TEST(sexy_prime_pairs_up_to, seven) {
    EXPECT_THAT(sexy_prime_pairs_up_to(7), ::testing::ElementsAre(::testing::Pair(1, 7)));
}

TEST(sexy_prime_pairs_up_to, forty_eight) {
    EXPECT_THAT(sexy_prime_pairs_up_to(48), ::testing::ElementsAre(
        ::testing::Pair(1, 7),
        ::testing::Pair(5, 11),
        ::testing::Pair(7, 13),
        ::testing::Pair(11, 17),
        ::testing::Pair(13, 19),
        ::testing::Pair(17, 23),
        ::testing::Pair(23, 29),
        ::testing::Pair(31, 37),
        ::testing::Pair(37, 43),
        ::testing::Pair(41, 47)
    ));
}

TEST(program_5_main, seven) {
    std::istringstream iss{ "7\n" };
    std::ostringstream oss{};
    problem_5_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Sexy prime pairs up to 7:\n\t(1, 7)"));
}
