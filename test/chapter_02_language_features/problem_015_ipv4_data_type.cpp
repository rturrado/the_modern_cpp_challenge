#include "chapter_02_language_features/problem_015_ipv4_data_type.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // istringstream, ostringstream


TEST(problem_15_main, ip_127_0_0_1_and_abc) {
    std::istringstream iss{ "127.0.0.1\nabc\nquit\n" };
    std::ostringstream oss{};
    problem_15_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("\tYou've entered a valid IPv4 address: 127.0.0.1\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("\tError: invalid IPv4 address: abc\n"));
    EXPECT_THAT(oss.str(), ::testing::EndsWith("\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n")));
}
