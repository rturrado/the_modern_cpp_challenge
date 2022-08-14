#include "chapter_12_networking_and_services/problem_097_bitcoin_exchange_rates.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_97_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_97_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Current bitcoin exchange rates:\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\\{ symbol: \\w\\w\\w, 15m: \\d+\\.\\d\\d, last: \\d+\\.\\d\\d, buy: \\d+\\.\\d\\d, sell: \\d+\\.\\d\\d \\},\n.*"
        "\\{ symbol: \\w\\w\\w, 15m: \\d+\\.\\d\\d, last: \\d+\\.\\d\\d, buy: \\d+\\.\\d\\d, sell: \\d+\\.\\d\\d \\}\n"
        "\\}\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
