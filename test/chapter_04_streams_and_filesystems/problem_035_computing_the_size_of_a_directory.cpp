#include "chapter_04_streams_and_filesystems/problem_035_computing_the_size_of_a_directory.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_35_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_35_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah\n"
    ));
}
