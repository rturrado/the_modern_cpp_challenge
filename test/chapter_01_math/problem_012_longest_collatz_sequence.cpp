#include "chapter_01_math/problem_012_longest_collatz_sequence.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

using namespace tmcppc::problem_12;


TEST(get_collatz_sequence_size, n_0) { EXPECT_EQ(get_collatz_sequence_size(0), 0); }
TEST(get_collatz_sequence_size, n_6) { EXPECT_EQ(get_collatz_sequence_size(6), 9); }
TEST(get_collatz_sequence_size, n_75_128_138_247) { EXPECT_EQ(get_collatz_sequence_size(75'128'138'247), 1229); }

TEST(get_collatz_sequence, n_0) {
    std::vector<size_t> result{};
    EXPECT_EQ(get_collatz_sequence(0), result);
}
TEST(get_collatz_sequence, n_6) { EXPECT_THAT(get_collatz_sequence(6), ::testing::ElementsAre(6, 3, 10, 5, 16, 8, 4, 2, 1)); }

TEST(get_longest_collatz_sequence_v1, n_0) { EXPECT_THAT(get_longest_collatz_sequence_v1(0), ::testing::Pair(0, 0)); }
TEST(get_longest_collatz_sequence_v1, n_10) { EXPECT_THAT(get_longest_collatz_sequence_v1(10), ::testing::Pair(9, 20)); }
TEST(get_longest_collatz_sequence_v1, n_1_000_000) { EXPECT_THAT(get_longest_collatz_sequence_v1(1'000'000),
    ::testing::Pair(837'799, 525)); }

TEST(get_longest_collatz_sequence_v2, n_0) { EXPECT_THAT(get_longest_collatz_sequence_v2(0), ::testing::Pair(0, 0)); }
TEST(get_longest_collatz_sequence_v2, n_10) { EXPECT_THAT(get_longest_collatz_sequence_v2(10), ::testing::Pair(9, 20)); }
TEST(get_longest_collatz_sequence_v2, n_1_000_000) { EXPECT_THAT(get_longest_collatz_sequence_v2(1'000'000),
    ::testing::Pair(837'799, 525));
}

TEST(problem_12_main, n_1_000_000) {
    std::ostringstream oss{};
    problem_12_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Number between 1 and 1000000 with longest Collatz sequence (525 elements) is: 837799\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}