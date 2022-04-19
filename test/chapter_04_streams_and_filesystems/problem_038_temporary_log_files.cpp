#include "chapter_04_streams_and_filesystems/problem_038_temporary_log_files.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_38_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_38_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah\n"
    ));
}
