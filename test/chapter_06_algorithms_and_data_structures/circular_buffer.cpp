#include "chapter_06_algorithms_and_data_structures/circular_buffer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream
#include <stdexcept>  // runtime_error
#include <utility>  // as_const

using tmcppc::data_structures::circular_buffer;


TEST(circular_buffer, DISABLED_zero_capacity) {
    EXPECT_THROW(circular_buffer<int>{ 0 }, std::runtime_error);
}
TEST(circular_buffer, DISABLED_nonzero_capacity) {
    circular_buffer<int> cb{ 5 };
    EXPECT_TRUE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 0);
    EXPECT_EQ(cb.capacity(), 5);
}
TEST(circular_buffer, DISABLED_push_back) {
    circular_buffer<int> cb{ 5 };
    cb.push_back(1);
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.capacity(), 5);
}
TEST(circular_buffer, DISABLED_push_back_fills_buffer) {
    circular_buffer<int> cb{ 1 };
    cb.push_back(1);
    EXPECT_FALSE(cb.empty());
    EXPECT_TRUE(cb.full());
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.capacity(), 1);
}
TEST(circular_buffer, DISABLED_push_back_on_full_buffer) {
    circular_buffer<int> cb{ 1 };
    cb.push_back(1);
    cb.push_back(2);
    EXPECT_FALSE(cb.empty());
    EXPECT_TRUE(cb.full());
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.capacity(), 1);
    EXPECT_EQ(cb.front(), 2);
    EXPECT_EQ(cb.back(), 2);
}
TEST(circular_buffer, DISABLED_pop_front) {
    circular_buffer<int> cb{ 5 };
    cb.push_back(1);
    cb.push_back(2);
    cb.pop_front();
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.front(), 2);
    EXPECT_EQ(cb.back(), 2);
}
TEST(circular_buffer, DISABLED_pop_front_empties_buffer) {
    circular_buffer<int> cb{ 5 };
    cb.push_back(1);
    cb.pop_front();
    EXPECT_TRUE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 0);
    EXPECT_EQ(cb.capacity(), 5);
}
TEST(circular_buffer, DISABLED_pop_front_on_full_buffer) {
    circular_buffer<int> cb{ 2 };
    cb.push_back(1);
    cb.push_back(2);
    cb.pop_front();
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.capacity(), 2);
    EXPECT_EQ(cb.front(), 2);
    EXPECT_EQ(cb.back(), 2);
}
TEST(circular_buffer, DISABLED_pop_back) {
    circular_buffer<int> cb{ 5 };
    cb.push_back(1);
    cb.push_back(2);
    cb.pop_back();
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.back(), 1);
    EXPECT_EQ(cb.back(), 1);
}
TEST(circular_buffer, DISABLED_pop_back_empties_buffer) {
    circular_buffer<int> cb{ 5 };
    cb.push_back(1);
    cb.pop_back();
    EXPECT_TRUE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 0);
    EXPECT_EQ(cb.capacity(), 5);
}
TEST(circular_buffer, DISABLED_pop_back_on_full_buffer) {
    circular_buffer<int> cb{ 2 };
    cb.push_back(1);
    cb.push_back(2);
    cb.pop_back();
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.capacity(), 2);
    EXPECT_EQ(cb.back(), 1);
    EXPECT_EQ(cb.back(), 1);
}
TEST(circular_buffer, DISABLED_pop_front_on_empty_buffer) {
    circular_buffer<int> cb{ 2 };
    EXPECT_THROW(cb.pop_front(), std::runtime_error);
}
TEST(circular_buffer, DISABLED_pop_back_on_empty_buffer) {
    circular_buffer<int> cb{ 2 };
    EXPECT_THROW(cb.pop_back(), std::runtime_error);
}
TEST(circular_buffer, DISABLED_front_on_empty_const_buffer) {
    circular_buffer<int> cb{ 5 };
    EXPECT_THROW((void)std::as_const(cb).front(), std::runtime_error);
}
TEST(circular_buffer, DISABLED_back_on_empty_const_buffer) {
    circular_buffer<int> cb{ 5 };
    EXPECT_THROW((void)std::as_const(cb).back(), std::runtime_error);
}
TEST(circular_buffer, DISABLED_front_on_empty_non_const_buffer) {
    circular_buffer<int> cb{ 5 };
    EXPECT_THROW((void)cb.front(), std::runtime_error);
}
TEST(circular_buffer, DISABLED_back_on_empty_non_const_buffer) {
    circular_buffer<int> cb{ 5 };
    EXPECT_THROW((void)cb.back(), std::runtime_error);
}
TEST(circular_buffer, DISABLED_front_and_back) {
    circular_buffer<int> cb{ 5 };
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.front(), 1);
    EXPECT_EQ(cb.back(), 3);
}
TEST(circular_buffer, DISABLED_clear) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.clear();
    EXPECT_TRUE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(cb.size(), 0);
    EXPECT_EQ(cb.capacity(), 3);
}
TEST(circular_buffer, DISABLED_begin) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(*cb.begin(), 1);
}
TEST(circular_buffer, DISABLED_end) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(++cb.begin(), cb.end());
}
TEST(circular_buffer, DISABLED_begin_on_const_buffer) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(*std::as_const(cb).begin(), 1);
}
TEST(circular_buffer, DISABLED_end_on_const_buffer) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(++std::as_const(cb).begin(), std::as_const(cb).end());
}
TEST(circular_buffer, DISABLED_cbegin) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(*std::as_const(cb).cbegin(), 1);
}
TEST(circular_buffer, DISABLED_cend) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(++std::as_const(cb).cbegin(), std::as_const(cb).cend());
}
TEST(circular_buffer, DISABLED_begin_free_function) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(*begin(cb), 1);
}
TEST(circular_buffer, DISABLED_end_free_function) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(++begin(cb), end(cb));
}
TEST(circular_buffer, DISABLED_begin_free_function_on_const_buffer) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(*begin(std::as_const(cb)), 1);
}
TEST(circular_buffer, DISABLED_end_free_function_on_const_buffer) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(++begin(std::as_const(cb)), end(std::as_const(cb)));
}
TEST(circular_buffer, DISABLED_cbegin_free_function) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(*cbegin(std::as_const(cb)), 1);
}
TEST(circular_buffer, DISABLED_cend_free_function) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    EXPECT_EQ(++cbegin(std::as_const(cb)), cend(std::as_const(cb)));
}
TEST(circular_buffer, DISABLED_fmt_print) {
    circular_buffer<int> cb{ 3 };
    cb.push_back(1);
    cb.push_back(2);
    std::ostringstream oss{};
    fmt::print(oss, "{}", cb);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("[1, 2, 0]"));
}
