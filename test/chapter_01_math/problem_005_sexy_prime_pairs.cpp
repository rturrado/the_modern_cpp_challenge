#include "chapter_01_math/problem_005_sexy_prime_pairs.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream
#include <utility>  // pair
#include <vector>


TEST(sexy_prime_pairs_up_to, zero) { auto ret{ sexy_prime_pairs_up_to(0) }; EXPECT_EQ(ret.size(), 0); }
TEST(sexy_prime_pairs_up_to, one) { auto ret{ sexy_prime_pairs_up_to(1) }; EXPECT_EQ(ret.size(), 0); }
TEST(sexy_prime_pairs_up_to, two) { auto ret{ sexy_prime_pairs_up_to(2) }; EXPECT_EQ(ret.size(), 0); }
TEST(sexy_prime_pairs_up_to, three) { auto ret{ sexy_prime_pairs_up_to(3) }; EXPECT_EQ(ret.size(), 0); }
TEST(sexy_prime_pairs_up_to, four) { auto ret{ sexy_prime_pairs_up_to(4) }; EXPECT_EQ(ret.size(), 0); }
TEST(sexy_prime_pairs_up_to, five) { auto ret{ sexy_prime_pairs_up_to(5) }; EXPECT_EQ(ret.size(), 0); }
TEST(sexy_prime_pairs_up_to, six) { auto ret{ sexy_prime_pairs_up_to(6) }; EXPECT_EQ(ret.size(), 0); }

TEST(sexy_prime_pairs_up_to, seven) {
    EXPECT_THAT(sexy_prime_pairs_up_to(7), ::testing::ElementsAre(std::pair<size_t, size_t>{ 1, 7 }));
}

TEST(sexy_prime_pairs_up_to, forty_eight) {
    EXPECT_THAT(sexy_prime_pairs_up_to(48), ::testing::ElementsAre(
        std::pair<size_t, size_t>{ 1, 7 },
        std::pair<size_t, size_t>{ 5, 11 },
        std::pair<size_t, size_t>{ 7, 13 },
        std::pair<size_t, size_t>{ 11, 17 },
        std::pair<size_t, size_t>{ 13, 19 },
        std::pair<size_t, size_t>{ 17, 23 },
        std::pair<size_t, size_t>{ 23, 29 },
        std::pair<size_t, size_t>{ 31, 37 },
        std::pair<size_t, size_t>{ 37, 43 },
        std::pair<size_t, size_t>{ 41, 47 }
    ));
}

TEST(program_5_main, seven) {
    std::istringstream iss{ "7\n" };
    std::ostringstream oss{};
    problem_5_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Sexy prime pairs up to 7:\n\t(1, 7)"));
}
