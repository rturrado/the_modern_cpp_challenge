#include "chapter_01_math/problem_013_computing_the_value_of_pi.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace tmcppc::problem_13;


TEST(compute_pi, n_10) { EXPECT_NEAR(compute_pi(10), 3.14159, 0.9); }
TEST(compute_pi, n_100) { EXPECT_NEAR(compute_pi(100), 3.14159, 0.2); }
TEST(compute_pi, n_1000) { EXPECT_NEAR(compute_pi(1'000), 3.14159, 0.1); }
TEST(compute_pi, n_10_000) { EXPECT_NEAR(compute_pi(10'000), 3.14159, 0.05); }
TEST(compute_pi, n_100_000) { EXPECT_NEAR(compute_pi(100'000), 3.14159, 0.01); }
TEST(compute_pi, n_1_000_000) { EXPECT_NEAR(compute_pi(1'000'000), 3.14159, 0.01); }
TEST(compute_pi, n_10_000_000) { EXPECT_NEAR(compute_pi(10'000'000), 3.14159, 0.01); }

TEST(problem_13_main, value_of_pi_with_a_precision_of_two_decimal_digits) {
    std::ostringstream oss{};
    problem_13_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Estimated value of pi: 3.14"));
    EXPECT_THAT(oss.str(), ::testing::EndsWith("\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
