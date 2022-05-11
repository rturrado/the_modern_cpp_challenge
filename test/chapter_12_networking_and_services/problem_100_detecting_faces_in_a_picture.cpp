#include "chapter_12_networking_and_services/problem_100_detecting_faces_in_a_picture.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_100_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_100_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
