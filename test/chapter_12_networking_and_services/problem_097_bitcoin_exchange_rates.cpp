#include "chapter_12_networking_and_services/problem_097_bitcoin_exchange_rates.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream


TEST(problem_97_main, output) {
    std::ostringstream oss{};
    problem_97_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Current bitcoin exchange rates:\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\\{ symbol: \\w\\w\\w, 15m: [0-9]+\\.[0-9][0-9], last: [0-9]+\\.[0-9][0-9], "
        "buy: [0-9]+\\.[0-9][0-9], sell: [0-9]+\\.[0-9][0-9] \\},\n.*"
        "\\{ symbol: \\w\\w\\w, 15m: [0-9]+\\.[0-9][0-9], last: [0-9]+\\.[0-9][0-9], "
        "buy: [0-9]+\\.[0-9][0-9], sell: [0-9]+\\.[0-9][0-9] \\}\n"
        "\\}\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
