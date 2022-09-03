#include "chapter_01_math/problem_002_greatest_common_divisor.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>  // numeric_limits
#include <sstream>  // istringstream, ostringstream
#include <stdexcept>  // runtime_error

using namespace tmcppc::problem_2;


TEST(gcd, minus_ten_and_ten) { EXPECT_THROW(gcd(-10, 10), std::runtime_error); }
TEST(gcd, ten_and_minus_ten) { EXPECT_THROW(gcd(10, -10), std::runtime_error); }
TEST(gcd, zero_and_zero) { EXPECT_THROW(gcd(0, 0), std::runtime_error); }
TEST(gcd, zero_and_max_int) { EXPECT_THROW(gcd(0, std::numeric_limits<int>::max()), std::runtime_error); }
TEST(gcd, max_int_and_zero) { EXPECT_THROW(gcd(std::numeric_limits<int>::max(), 0), std::runtime_error); }

TEST(gcd, one_and_max_int) { EXPECT_EQ(gcd(1, std::numeric_limits<int>::max()), 1); }
TEST(gcd, max_int_and_one) { EXPECT_EQ(gcd(std::numeric_limits<int>::max(), 1), 1); }
TEST(gcd, ten_and_max_int) { EXPECT_EQ(gcd(10, std::numeric_limits<int>::max()), 1); }
TEST(gcd, max_int_and_ten) { EXPECT_EQ(gcd(std::numeric_limits<int>::max(), 10), 1); }
TEST(gcd, fifty_and_ten) { EXPECT_EQ(gcd(50, 10), 10); }
TEST(gcd, ten_and_fifty) { EXPECT_EQ(gcd(10, 50), 10); }
TEST(gcd, fifty_and_fifteen) { EXPECT_EQ(gcd(50, 15), 5); }
TEST(gcd, fifteen_and_fifty) { EXPECT_EQ(gcd(15, 50), 5); }

TEST(problem_2_main, m_15_n_50) {
    std::istringstream iss{ "15\n50\n" };
    std::ostringstream oss{};
    problem_2_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("The greatest common divisor of 15 and 50 is: 5\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
