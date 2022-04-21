#include "chapter_08_design_patterns/problem_070_approval_system.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_70_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_70_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

