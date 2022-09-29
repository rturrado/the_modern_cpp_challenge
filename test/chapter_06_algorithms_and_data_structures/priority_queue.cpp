#include "chapter_06_algorithms_and_data_structures/priority_queue.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>  // runtime_error
#include <utility>  // as_const
#include <vector>

using tmcppc::data_structures::priority_queue;


TEST(priority_queue, default_constructor) {
    EXPECT_TRUE(priority_queue<int>{}.empty());
}
TEST(priority_queue, custom_constructor) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_FALSE(pq.empty());
    EXPECT_EQ(pq.size(), 3);
    std::vector<int> w{ pq.cbegin(), pq.cend() };
    EXPECT_THAT(w, ::testing::UnorderedElementsAre(1, 5, 10));
    EXPECT_EQ(pq.top(), 10);
}
TEST(priority_queue, custom_constructor_with_compare_function) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int, std::greater<int>> pq{ v.cbegin(), v.cend() };
    EXPECT_FALSE(pq.empty());
    EXPECT_EQ(pq.size(), 3);
    std::vector<int> w{ pq.cbegin(), pq.cend() };
    EXPECT_THAT(w, ::testing::UnorderedElementsAre(1, 5, 10));
    EXPECT_EQ(pq.top(), 1);
}
TEST(priority_queue, push) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    pq.push(7);
    std::vector<int> w{ pq.cbegin(), pq.cend() };
    EXPECT_THAT(w, ::testing::UnorderedElementsAre(1, 5, 7, 10));
}
TEST(priority_queue, pop_on_empty_queue) {
    EXPECT_THROW(priority_queue<int>{}.pop(), std::runtime_error);
}
TEST(priority_queue, pop) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    pq.push(7);
    pq.pop();
    std::vector<int> w{ pq.cbegin(), pq.cend() };
    EXPECT_THAT(w, ::testing::UnorderedElementsAre(1, 5, 7));
}
TEST(priority_queue, top_on_empty_queue) {
    EXPECT_THROW((void) priority_queue<int>{}.top(), std::runtime_error);
}
TEST(priority_queue, top_on_empty_const_queue) {
    priority_queue<int> pq{};
    EXPECT_THROW((void) std::as_const(pq).top(), std::runtime_error);
}
TEST(priority_queue, top) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(pq.top(), 10);
}
TEST(priority_queue, top_on_const_queue) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(std::as_const(pq).top(), 10);
}
TEST(priority_queue, size) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(pq.size(), 3);
}
TEST(priority_queue, empty) {
    EXPECT_TRUE(priority_queue<int>{}.empty());
}
TEST(priority_queue, not_empty) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_FALSE(pq.empty());
}
TEST(priority_queue, swap) {
    std::vector<int> v{ 1, 5, 10 };
    std::vector<int> w{ 100, 500 };
    priority_queue<int> pq_1{ v.cbegin(), v.cend() };
    priority_queue<int> pq_2{ w.cbegin(), w.cend() };
    pq_1.swap(pq_2);
    EXPECT_EQ(pq_1.size(), 2);
    EXPECT_EQ(pq_2.size(), 3);
    EXPECT_EQ(pq_1.top(), 500);
    EXPECT_EQ(pq_2.top(), 10);
    std::vector<int> vv{ pq_1.cbegin(), pq_1.cend() };
    std::vector<int> ww{ pq_2.cbegin(), pq_2.cend() };
    EXPECT_THAT(vv, ::testing::UnorderedElementsAre(100, 500));
    EXPECT_THAT(ww, ::testing::UnorderedElementsAre(1, 5, 10));
}
TEST(priority_queue, swap_free_function) {
    std::vector<int> v{ 1, 5, 10 };
    std::vector<int> w{ 100, 500 };
    priority_queue<int> pq_1{ v.cbegin(), v.cend() };
    priority_queue<int> pq_2{ w.cbegin(), w.cend() };
    swap(pq_1, pq_2);
    EXPECT_EQ(pq_1.size(), 2);
    EXPECT_EQ(pq_2.size(), 3);
    EXPECT_EQ(pq_1.top(), 500);
    EXPECT_EQ(pq_2.top(), 10);
    std::vector<int> vv{ pq_1.cbegin(), pq_1.cend() };
    std::vector<int> ww{ pq_2.cbegin(), pq_2.cend() };
    EXPECT_THAT(vv, ::testing::UnorderedElementsAre(100, 500));
    EXPECT_THAT(ww, ::testing::UnorderedElementsAre(1, 5, 10));
}
TEST(priority_queue, begin) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(*pq.begin(), 10);
}
TEST(priority_queue, end) {
    std::vector<int> v{ 1 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(++pq.begin(), pq.end());
}
TEST(priority_queue, begin_on_const_buffer) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(*std::as_const(pq).begin(), 10);
}
TEST(priority_queue, end_on_const_buffer) {
    std::vector<int> v{ 1 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(++std::as_const(pq).begin(), std::as_const(pq).end());
}
TEST(priority_queue, cbegin) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(*std::as_const(pq).cbegin(), 10);
}
TEST(priority_queue, cend) {
    std::vector<int> v{ 1 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(++std::as_const(pq).cbegin(), std::as_const(pq).cend());
}
TEST(priority_queue, begin_free_function) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(*begin(pq), 10);
}
TEST(priority_queue, end_free_function) {
    std::vector<int> v{ 1 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(++begin(pq), end(pq));
}
TEST(priority_queue, begin_free_function_on_const_buffer) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(*begin(std::as_const(pq)), 10);
}
TEST(priority_queue, end_free_function_on_const_buffer) {
    std::vector<int> v{ 1 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(++begin(std::as_const(pq)), end(std::as_const(pq)));
}
TEST(priority_queue, cbegin_free_function) {
    std::vector<int> v{ 1, 5, 10 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(*cbegin(std::as_const(pq)), 10);
}
TEST(priority_queue, cend_free_function) {
    std::vector<int> v{ 1 };
    priority_queue<int> pq{ v.cbegin(), v.cend() };
    EXPECT_EQ(++cbegin(std::as_const(pq)), cend(std::as_const(pq)));
}
