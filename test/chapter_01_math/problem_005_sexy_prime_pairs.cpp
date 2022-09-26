#include "chapter_01_math/problem_005_sexy_prime_pairs.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <vector>

using namespace tmcppc::problem_5;


TEST(sexy_prime_pairs_up_to, limit_0) { EXPECT_TRUE(sexy_prime_pairs_up_to(0).empty()); }
TEST(sexy_prime_pairs_up_to, limit_1) { EXPECT_TRUE(sexy_prime_pairs_up_to(1).empty()); }
TEST(sexy_prime_pairs_up_to, limit_2) { EXPECT_TRUE(sexy_prime_pairs_up_to(2).empty()); }
TEST(sexy_prime_pairs_up_to, limit_3) { EXPECT_TRUE(sexy_prime_pairs_up_to(3).empty()); }
TEST(sexy_prime_pairs_up_to, limit_4) { EXPECT_TRUE(sexy_prime_pairs_up_to(4).empty()); }
TEST(sexy_prime_pairs_up_to, limit_5) { EXPECT_TRUE(sexy_prime_pairs_up_to(5).empty()); }
TEST(sexy_prime_pairs_up_to, limit_6) { EXPECT_TRUE(sexy_prime_pairs_up_to(6).empty()); }

TEST(sexy_prime_pairs_up_to, limit_7) {
    EXPECT_THAT(sexy_prime_pairs_up_to(7), ::testing::ElementsAre(::testing::Pair<size_t, size_t>(1, 7)));
}

TEST(sexy_prime_pairs_up_to, limit_48) {
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

TEST(program_5_main, limit_7) {
    std::istringstream iss{ "7\n" };
    std::ostringstream oss{};
    problem_5_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Sexy prime pairs up to 7:\n\t(1, 7)\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
