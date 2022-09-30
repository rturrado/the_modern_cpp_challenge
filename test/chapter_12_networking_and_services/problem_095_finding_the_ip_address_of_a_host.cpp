#include "chapter_12_networking_and_services/problem_095_finding_the_ip_address_of_a_host.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream


TEST(problem_95_main, output) {
    std::ostringstream oss{};
    problem_95_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Getting IPv4 addresses for host = 'localhost' and service = '8080'\n"
        "\t127.0.0.1\n"
    ));
#if defined(_WIN32)
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Getting IPv4 addresses for host = 'www.boost.org' and service = 'http'\n"
        "\t\\d+\\.\\d+\\.\\d+\\.\\d+\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Getting IPv4 addresses for host = 'www.google.com' and service = 'https'\n"
        "\t\\d+\\.\\d+\\.\\d+\\.\\d+\n"
    ));
#elif defined(__GNUC__)
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Getting IPv4 addresses for host = 'www.boost.org' and service = 'http'\n"
        "\t[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Getting IPv4 addresses for host = 'www.google.com' and service = 'https'\n"
        "\t[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\n"
    ));
#endif
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Getting IPv4 addresses for host = 'www.---.com' and service = 'http'\n"
        "\tError: resolve: .*\n"  // error messages are platform dependent
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Getting IPv4 addresses for host = 'www.boost.org' and service = 'blah'\n"
        "\tError: resolve: .*\n\n"  // error messages are platform dependent
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
