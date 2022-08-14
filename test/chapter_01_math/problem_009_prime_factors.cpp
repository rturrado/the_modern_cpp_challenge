#include "chapter_01_math/problem_009_prime_factors.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(problem_9_main, DISABLED_n_100) {
    std::istringstream iss{ "100\n" };
    std::ostringstream oss{};
    problem_9_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Prime factors of 100: [1, 2, 2, 5, 5]\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
