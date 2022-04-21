#include "chapter_06_algorithms_and_data_structures/problem_047_double_buffer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_47_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_47_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
