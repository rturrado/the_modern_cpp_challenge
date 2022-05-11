#include "chapter_12_networking_and_services/problem_099_translating_text.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_099_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_099_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
