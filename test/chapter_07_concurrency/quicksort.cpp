#include "chapter_07_concurrency/quicksort.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>  // generate, shuffle
#include <functional>  // less
#include <numeric>  // iota
#include <random>  // mt19937, random_device
#include <ranges>
#include <vector>


TEST(partition, DISABLED_range_of_same_repeated_number) {
    std::vector<int> v(1000, 15);
    EXPECT_EQ(tmcppc::algorithm::partition(v.begin(), v.end(), std::less<int>{}), std::prev(v.end()));
}
TEST(partition, DISABLED_range_of_numbers_in_descending_order) {
    std::vector<int> v(1000);
    std::iota(v.rbegin(), v.rend(), 1);
    EXPECT_EQ(tmcppc::algorithm::partition(v.begin(), v.end(), std::less<int>{}), std::prev(v.end()));
}
TEST(partition, DISABLED_range_of_numbers_in_ascending_order) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), 1);
    EXPECT_EQ(tmcppc::algorithm::partition(v.begin(), v.end(), std::less<int>{}), v.begin());
}
TEST(partition, DISABLED_range_of_numbers_in_ascending_and_descending_order) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.begin() + v.size() / 2, 1);
    std::iota(v.rbegin(), v.rbegin() + v.size() / 2, 1);
    EXPECT_EQ(tmcppc::algorithm::partition(v.begin(), v.end(), std::less<int>{}), std::next(v.begin()));
}
TEST(partition, DISABLED_compare) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), 1);
    EXPECT_EQ(tmcppc::algorithm::partition(v.begin(), v.end(), std::greater<int>{}), std::prev(v.end()));
}


TEST(quicksort, DISABLED_empty_range) {
    std::vector<int> v{};
    auto w{ v };
    tmcppc::algorithm::quicksort(v.begin(), v.end());
    EXPECT_EQ(v, w);
}
TEST(quicksort, DISABLED_range_of_same_repeated_number) {
    std::vector<int> v(1000, 15);
    auto w{ v };
    tmcppc::algorithm::quicksort(v.begin(), v.end());
    EXPECT_EQ(v, w);
}
TEST(quicksort, DISABLED_range_of_numbers_in_descending_order) {
    std::vector<int> v(1000);
    std::iota(v.rbegin(), v.rend(), 1);
    std::vector<int> w(1000);
    std::iota(w.begin(), w.end(), 1);
    tmcppc::algorithm::quicksort(v.begin(), v.end());
    EXPECT_EQ(v, w);
}
TEST(quicksort, DISABLED_range_of_numbers_in_ascending_order) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), 1);
    auto w{ v };
    tmcppc::algorithm::quicksort(v.begin(), v.end());
    EXPECT_EQ(v, w);
}
TEST(quicksort, DISABLED_range_of_numbers_in_ascending_and_descending_order) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.begin() + v.size() / 2, 1);
    std::iota(v.rbegin(), v.rbegin() + v.size() / 2, 1);
    std::vector<int> w(1000);
    std::ranges::generate(w, [i = 1]() mutable {
        auto j{ (i % 2 == 0) ? (i / 2) : (i / 2 + 1) };
        ++i;
        return j;
    });
    tmcppc::algorithm::quicksort(v.begin(), v.end());
    EXPECT_EQ(v, w);
}
TEST(quicksort, DISABLED_compare) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), 1);
    std::vector<int> w(1000);
    std::iota(w.rbegin(), w.rend(), 1);
    tmcppc::algorithm::quicksort(v.begin(), v.end(), std::greater<int>{});
    EXPECT_EQ(v, w);
}


TEST(parallel_quicksort, DISABLED_range_of_more_than_100_000_numbers) {
    std::vector<int> v(250'000);
    std::iota(v.begin(), v.end(), 1);
    std::iota(v.rbegin(), v.rbegin() + v.size() / 2, 1);
    std::ranges::shuffle(v, std::mt19937{ std::random_device{}() });
    std::vector<int> w(250'000);
    std::ranges::generate(w, [i = 1]() mutable {
        auto j{ (i % 2 == 0) ? (i / 2) : (i / 2 + 1) };
        ++i;
        return j;
    });
    tmcppc::algorithm::parallel_quicksort(v.begin(), v.end());
    EXPECT_EQ(v, w);
}
