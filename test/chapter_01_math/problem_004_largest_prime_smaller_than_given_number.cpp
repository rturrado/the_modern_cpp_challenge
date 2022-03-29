#include "chapter_01_math/problem_004_largest_prime_smaller_than_given_number.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream

TEST(biggest_prime_smaller_than, zero) { EXPECT_EQ(biggest_prime_smaller_than(0), 0); }
TEST(biggest_prime_smaller_than, one) { EXPECT_EQ(biggest_prime_smaller_than(1), 0); }
TEST(biggest_prime_smaller_than, two) { EXPECT_EQ(biggest_prime_smaller_than(2), 1); }
TEST(biggest_prime_smaller_than, twenty) { EXPECT_EQ(biggest_prime_smaller_than(20), 19); }

TEST(problem_4_main, forty_eight) {
    std::istringstream iss{ "48\n" };
    std::ostringstream oss{};
    problem_4_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Biggest prime number smaller than 48 is: 47"));
}
