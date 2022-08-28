#include "chapter_02_language_features/problem_016_enumerating_ipv4_addresses_in_a_range.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(problem_16_main, invalid_and_invalid_range_and_valid) {
    std::istringstream iss{ "127.0.0.1\n300.300.300.300\n127.0.0.1 1.1.1.1\n127.0.0.1 127.0.0.5\n" };
    std::ostringstream oss{};
    problem_16_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("\tError: invalid input.\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("\tError: range start address is bigger than range end address.\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "\t127.0.0.1\n"
        "\t127.0.0.2\n"
        "\t127.0.0.3\n"
        "\t127.0.0.4\n"
        "\t127.0.0.5\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
