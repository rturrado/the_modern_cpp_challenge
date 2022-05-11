#include "chapter_12_networking_and_services/problem_095_finding_the_ip_address_of_a_host.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_095_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_095_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
