#include "chapter_06_algorithms_and_data_structures/problem_046_circular_buffer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_46_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_46_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

