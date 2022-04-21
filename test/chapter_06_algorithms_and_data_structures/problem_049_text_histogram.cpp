#include "chapter_06_algorithms_and_data_structures/problem_049_text_histogram.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_49_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_49_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
