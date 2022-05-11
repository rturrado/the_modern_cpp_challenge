#include "chapter_12_networking_and_services/problem_097_bitcoin_exchange_rates.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_097_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_097_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
