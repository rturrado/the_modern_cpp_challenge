#include "chapter_10_archives_images_and_databases/problem_087_handling_images_in_an_sqlite_db.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_87_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_87_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
