#include "chapter_06_algorithms_and_data_structures/problem_055_zip_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_55_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_55_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

