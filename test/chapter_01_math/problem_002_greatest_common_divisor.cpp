#include "chapter_01_math/problem_002_greatest_common_divisor.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>  // numeric_limits
#include <sstream>  // istringstream, ostringstream


TEST(gcd, minus_ten_and_ten) {
    std::ostringstream oss{};
    EXPECT_EQ(gcd(oss, -10, 10), -1);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: calling gcd(m, n) with a negative or zero value.\n"));
}
TEST(gcd, ten_and_minus_ten) {
    std::ostringstream oss{};
    EXPECT_EQ(gcd(oss, 10, -10), -1);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: calling gcd(m, n) with a negative or zero value.\n"));
}
TEST(gcd, zero_and_zero) {
    std::ostringstream oss{};
    EXPECT_EQ(gcd(oss, 0, 0), -1);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: calling gcd(m, n) with a negative or zero value.\n"));
}
TEST(gcd, zero_and_max_int) {
    std::ostringstream oss{};
    EXPECT_EQ(gcd(oss, 0, std::numeric_limits<int>::max()), -1);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: calling gcd(m, n) with a negative or zero value.\n"));
}
TEST(gcd, max_int_and_zero) {
    std::ostringstream oss{};
    EXPECT_EQ(gcd(oss, std::numeric_limits<int>::max(), 0), -1);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: calling gcd(m, n) with a negative or zero value.\n"));
}
TEST(gcd, one_and_max_int) { EXPECT_EQ(gcd(1, std::numeric_limits<int>::max()), 1); }
TEST(gcd, max_int_and_one) { EXPECT_EQ(gcd(std::numeric_limits<int>::max(), 1), 1); }
TEST(gcd, ten_and_max_int) { EXPECT_EQ(gcd(10, std::numeric_limits<int>::max()), 1); }
TEST(gcd, max_int_and_ten) { EXPECT_EQ(gcd(std::numeric_limits<int>::max(), 10), 1); }
TEST(gcd, fifty_and_ten) { EXPECT_EQ(gcd(50, 10), 10); }
TEST(gcd, ten_and_fifty) { EXPECT_EQ(gcd(10, 50), 10); }
TEST(gcd, fifty_and_fifteen) { EXPECT_EQ(gcd(50, 15), 5); }
TEST(gcd, fifteen_and_fifty) { EXPECT_EQ(gcd(15, 50), 5); }

TEST(problem_2_main, fifteen_and_fifty) {
    std::istringstream iss{ "15\n50\n" };
    std::ostringstream oss{};
    problem_2_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("The greatest common divisor of 15 and 50 is: 5"));
}
