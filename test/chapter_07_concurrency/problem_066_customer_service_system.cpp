#include "chapter_07_concurrency/problem_066_customer_service_system.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_66_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_66_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
