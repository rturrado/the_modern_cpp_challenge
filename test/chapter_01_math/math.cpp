#include "chapter_01_math/math.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace tmcppc::math;


TEST(is_prime, char_0) { EXPECT_EQ(is_prime<char>(0), true); }
TEST(is_prime, int_0) { EXPECT_EQ(is_prime<int>(0), true); }
TEST(is_prime, long_0) { EXPECT_EQ(is_prime<long>(0), true); }
TEST(is_prime, size_t_0) { EXPECT_EQ(is_prime<size_t>(0), true); }
TEST(is_prime, int_1) { EXPECT_EQ(is_prime<int>(1), true); }
TEST(is_prime, int_2) { EXPECT_EQ(is_prime<int>(2), true); }
TEST(is_prime, int_4) { EXPECT_EQ(is_prime<int>(4), false); }

TEST(prime_factors, char_0) { EXPECT_THAT(prime_factors<char>(0), ::testing::ElementsAre(1)); }
TEST(prime_factors, int_0) { EXPECT_THAT(prime_factors<int>(0), ::testing::ElementsAre(1)); }
TEST(prime_factors, long_0) { EXPECT_THAT(prime_factors<long>(0), ::testing::ElementsAre(1)); }
TEST(prime_factors, size_t_0) { EXPECT_THAT(prime_factors<size_t>(0), ::testing::ElementsAre(1)); }
TEST(prime_factors, int_1) { EXPECT_THAT(prime_factors<int>(1), ::testing::ElementsAre(1)); }
TEST(prime_factors, int_10) { EXPECT_THAT(prime_factors<int>(10), ::testing::ElementsAre(1, 2, 5)); }
TEST(prime_factors, int_100) { EXPECT_THAT(prime_factors<int>(100), ::testing::ElementsAre(1, 2, 2, 5, 5)); }

TEST(divisors, char_0) { EXPECT_THAT(divisors<char>(0), ::testing::ElementsAre(1)); }
TEST(divisors, int_0) { EXPECT_THAT(divisors<int>(0), ::testing::ElementsAre(1)); }
TEST(divisors, long_0) { EXPECT_THAT(divisors<long>(0), ::testing::ElementsAre(1)); }
TEST(divisors, size_t_0) { EXPECT_THAT(divisors<size_t>(0), ::testing::ElementsAre(1)); }
TEST(divisors, int_1) { EXPECT_THAT(divisors<int>(1), ::testing::ElementsAre(1)); }
TEST(divisors, int_10) { EXPECT_THAT(divisors<int>(10), ::testing::ElementsAre(1, 2, 5)); }
TEST(divisors, int_100) { EXPECT_THAT(divisors<int>(100), ::testing::ElementsAre(1, 2, 4, 5, 10, 20, 25, 50)); }

TEST(divisors_sum, char_0) { EXPECT_EQ(divisors_sum<char>(0), 1); }
TEST(divisors_sum, int_1) { EXPECT_EQ(divisors_sum<int>(1), 1); }
TEST(divisors_sum, long_10) { EXPECT_EQ(divisors_sum<long>(10), 8); }
TEST(divisors_sum, size_t_100) { EXPECT_EQ(divisors_sum<size_t>(100), 117); }
