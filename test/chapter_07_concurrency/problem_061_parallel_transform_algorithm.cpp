#include "chapter_07_concurrency/problem_061_parallel_transform_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream
#include <vector>

using tmcppc::algorithm::parallel_transform;


TEST(parallel_transform, empty_input_range) {
    std::vector<int> v{};
    std::vector<int> w(v.size());
    parallel_transform(v.cbegin(), v.cend(), w.begin(), [](int i) { return i * i; });
    EXPECT_TRUE(v.empty());
    EXPECT_TRUE(w.empty());
    EXPECT_EQ(v, w);
}
TEST(parallel_transform, non_empty_output_range) {
    std::vector<int> v{ 1, 2 };
    std::vector<int> w{ 3, 4, 5 };
    parallel_transform(v.cbegin(), v.cend(), w.begin(), [](int i) { return i * i * i; });
    EXPECT_EQ(w.size(), 3);
    EXPECT_THAT(w, ::testing::ElementsAre(1, 8, 5));
}
TEST(parallel_transform, output_range_is_same_as_input_range) {
    std::vector<int> v{ 1, 2 };
    parallel_transform(v.cbegin(), v.cend(), v.begin(), [](int i) { return i + i; });
    EXPECT_EQ(v.size(), 2);
    EXPECT_THAT(v, ::testing::ElementsAre(2, 4));
}
TEST(parallel_transform, zero_thread_pool_size) {
    std::vector<int> v{ 1, 2 };
    std::vector<int> w(v.size());
    parallel_transform(v.cbegin(), v.cend(), w.begin(), [](int i) { return i * 3; }, 0);
    EXPECT_EQ(w.size(), 2);
    EXPECT_THAT(w, ::testing::ElementsAre(3, 6));
}
TEST(parallel_transform, zero_block_size) {
    std::vector<int> v{ 1, 2 };
    std::vector<int> w(v.size());
    parallel_transform(v.cbegin(), v.cend(), w.begin(), [](int i) { return i * 3; }, 4, 0);
    EXPECT_EQ(w.size(), 2);
    EXPECT_THAT(w, ::testing::ElementsAre(3, 6));
}


TEST(problem_61_main, output) {
    std::ostringstream oss{};
    problem_61_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "v = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]\n"
        "\n"
        "std::transform(v); v = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]\n"
        "std::transform(std::execution::par, v); v = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]\n"
        "parallel_transform(v); v = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
