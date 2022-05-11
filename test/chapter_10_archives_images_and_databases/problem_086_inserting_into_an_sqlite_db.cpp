#include "chapter_10_archives_images_and_databases/problem_086_inserting_into_an_sqlite_db.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_86_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_86_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
