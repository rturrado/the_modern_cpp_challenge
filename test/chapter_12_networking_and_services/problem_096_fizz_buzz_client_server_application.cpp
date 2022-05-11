#include "chapter_12_networking_and_services/problem_096_fizz_buzz_client_server_application.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_096_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_096_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
