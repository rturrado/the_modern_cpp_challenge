#include "chapter_12_networking_and_services/problem_098_fetching_emails_using_imap.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_098_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_098_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
