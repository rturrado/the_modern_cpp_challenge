#include "chapter_10_archives_images_and_databases/problem_085_reading_from_an_sqlite_db.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_85_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_85_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
