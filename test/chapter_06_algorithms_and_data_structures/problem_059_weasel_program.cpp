#include "chapter_06_algorithms_and_data_structures/problem_059_weasel_program.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cmath>  // abs
#include <numeric>  // transform_reduce
#include <sstream>  // ostringstream

using namespace tmcppc::weasel;


TEST(weasel_sequence, constructor_with_empty_target) {
    EXPECT_TRUE(weasel_sequence{ "" }.str().empty());
}
TEST(weasel_sequence, mutate) {
    weasel_sequence ws{ "METHINKS IT IS LIKE A WEASEL" };
    auto str_before_mutation{ ws.str() };
    ws.mutate();
    auto str_after_mutation{ ws.str() };
    EXPECT_TRUE(
        std::transform_reduce(
            std::cbegin(str_before_mutation), std::cend(str_before_mutation), std::cbegin(str_after_mutation),
            static_cast<size_t>(0),
            std::plus<>{},
            [](char b, char a) { return (b == a) ? 0 : 1; }
        )
        <= 1
    );
}
TEST(weasel_sequence, score) {
    weasel_sequence ws{ "METHINKS IT IS LIKE A WEASEL" };
    auto score_before_mutation{ ws.score() };
    ws.mutate();
    auto score_after_mutation{ ws.score() };
    EXPECT_TRUE(std::abs(score_before_mutation - score_after_mutation) <= 1);
}
TEST(weasel_sequence, end) {
    std::string target{ "METHINKS IT IS LIKE A WEASEL" };
    weasel_sequence ws{ target };
    EXPECT_EQ(ws.end(), ws.str() == target);
}
TEST(weasel_sequence, size) {
    std::string target{ "METHINKS IT IS LIKE A WEASEL" };
    EXPECT_EQ(weasel_sequence{ target }.str().size(), target.size());
}


TEST(problem_59_main, output) {
    std::ostringstream oss{};
    problem_59_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("METHINKS IT IS LIKE A WEASEL"));
    EXPECT_THAT(oss.str(), ::testing::EndsWith("\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
