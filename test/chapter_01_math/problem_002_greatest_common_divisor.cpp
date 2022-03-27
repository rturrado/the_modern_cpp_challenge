#include "chapter_01_math/problem_002_greatest_common_divisor.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>  // numeric_limits
#include <sstream>  // istringstream, ostringstream


TEST(gcd, zero_and_zero) {
    constexpr size_t m{ 0 };
    constexpr size_t n{ 0 };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 1);
}

TEST(gcd, zero_and_max_size_t) {
    constexpr size_t m{ 0 };
    constexpr size_t n{ std::numeric_limits<size_t>::max() };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 1);
}

TEST(gcd, max_size_t_and_zero) {
    constexpr size_t m{ std::numeric_limits<size_t>::max() };
    constexpr size_t n{ 0 };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 1);
}

TEST(gcd, one_and_max_size_t) {
    constexpr size_t m{ 1 };
    constexpr size_t n{ std::numeric_limits<size_t>::max() };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 1);
}

TEST(gcd, max_size_t_and_one) {
    constexpr size_t m{ std::numeric_limits<size_t>::max() };
    constexpr size_t n{ 1 };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 1);
}

TEST(gcd, ten_and_max_size_t) {
    constexpr size_t m{ 10 };
    constexpr size_t n{ std::numeric_limits<size_t>::max() };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 5);
}

TEST(gcd, max_size_t_and_ten) {
    constexpr size_t m{ std::numeric_limits<size_t>::max() };
    constexpr size_t n{ 10 };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 5);
}

TEST(gcd, fifty_and_ten) {
    constexpr size_t m{ 50 };
    constexpr size_t n{ 10 };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 10);
}

TEST(gcd, ten_and_fifty) {
    constexpr size_t m{ 10 };
    constexpr size_t n{ 50 };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 10);
}

TEST(gcd, fifty_and_fifteen) {
    constexpr size_t m{ 50 };
    constexpr size_t n{ 15 };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 5);
}

TEST(gcd, fifteen_and_fifty) {
    constexpr size_t m{ 15 };
    constexpr size_t n{ 50 };
    auto ret{ gcd(m, n) };
    EXPECT_EQ(ret, 5);
}

TEST(problem_2_main, fifteen_and_fifty) {
    std::istringstream iss{ "15\n50\n" };
    std::ostringstream oss{};
    problem_2_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("The greatest common divisor of 15 and 50 is: 5"));
}
