#include "chapter_08_design_patterns/problem_072_computing_order_price_with_discounts.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_72_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_72_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
