#include "chapter_01_math/digits.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace rtc::math;


TEST(size, n_0) { digits<size_t> d{}; EXPECT_EQ(d.size(), 1); }
TEST(size, n_1000) { digits<size_t> d{1000}; EXPECT_EQ(d.size(), 4); }

TEST(to_string, n_0) { digits<size_t> d{}; EXPECT_EQ(d.to_string(), "0"); }
TEST(to_string, n_1000) { digits<size_t> d{ 1000 }; EXPECT_EQ(d.to_string(), "1000"); }

TEST(pre_increment, n_0) { digits<size_t> d{}; EXPECT_EQ((++d).to_string(), "1"); }
TEST(pre_increment, n_9) { digits<size_t> d{9}; EXPECT_EQ((++d).to_string(), "10"); }

TEST(pre_decrement, n_0) { digits<size_t> d{}; EXPECT_EQ((--d).to_string(), "0"); }
TEST(pre_decrement, n_10) { digits<size_t> d{10}; EXPECT_EQ((--d).to_string(), "9"); }
