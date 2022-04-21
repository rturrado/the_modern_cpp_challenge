#include "chapter_08_design_patterns/problem_071_observable_vector_container.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_71_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_71_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

