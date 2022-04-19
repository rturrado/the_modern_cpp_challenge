#include "chapter_04_streams_and_filesystems/problem_036_deleting_files_older_than_a_given_date.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_36_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_36_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah\n"
    ));
}
