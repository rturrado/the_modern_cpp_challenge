#include "chapter_12_networking_and_services/problem_095_finding_the_ip_address_of_a_host.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_95_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_95_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Getting IPv4 addresses for host = 'localhost' and service = '8080'\n"
        "\t127.0.0.1\n"
        "Getting IPv4 addresses for host = 'www.boost.org' and service = 'http'\n"
        "\t\\d+\\.\\d+\\.\\d+\\.\\d+\n"
        "Getting IPv4 addresses for host = 'www.google.com' and service = 'https'\n"
        "\t\\d+\\.\\d+\\.\\d+\\.\\d+\n"
    ));
}
