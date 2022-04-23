#include "chapter_01_math/digits.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace tmcppc::math;


TEST(size, DISABLED_n_0) { digits<size_t> d{}; EXPECT_EQ(d.size(), 1); }
TEST(size, DISABLED_n_1000) { digits<size_t> d{1000}; EXPECT_EQ(d.size(), 4); }

TEST(to_string, DISABLED_n_0) { digits<size_t> d{}; EXPECT_EQ(d.to_string(), "0"); }
TEST(to_string, DISABLED_n_1000) { digits<size_t> d{ 1000 }; EXPECT_EQ(d.to_string(), "1000"); }

TEST(pre_increment, DISABLED_n_0) { digits<size_t> d{}; EXPECT_EQ((++d).to_string(), "1"); }
TEST(pre_increment, DISABLED_n_9) { digits<size_t> d{9}; EXPECT_EQ((++d).to_string(), "10"); }

TEST(pre_decrement, DISABLED_n_0) { digits<size_t> d{}; EXPECT_EQ((--d).to_string(), "0"); }
TEST(pre_decrement, DISABLED_n_10) { digits<size_t> d{10}; EXPECT_EQ((--d).to_string(), "9"); }
