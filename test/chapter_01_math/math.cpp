#include "chapter_01_math/math.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(is_prime, char_zero) { EXPECT_EQ(is_prime<char>(0), true); }
TEST(is_prime, int_zero) { EXPECT_EQ(is_prime<int>(0), true); }
TEST(is_prime, long_zero) { EXPECT_EQ(is_prime<long>(0), true); }
TEST(is_prime, size_t_zero) { EXPECT_EQ(is_prime<size_t>(0), true); }
TEST(is_prime, int_one) { EXPECT_EQ(is_prime<int>(1), true); }
TEST(is_prime, int_two) { EXPECT_EQ(is_prime<int>(2), true); }
TEST(is_prime, int_four) { EXPECT_EQ(is_prime<int>(4), false); }
