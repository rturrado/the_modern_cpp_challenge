#include "chapter_12_networking_and_services/problem_095_finding_the_ip_address_of_a_host.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exception>
#include <sstream>  // ostringstream

using namespace tmcppc::problem_95;


TEST(get_host_ipv4_addresses, empty_host) {
    EXPECT_THAT(get_host_ipv4_addresses("", "8080"), ::testing::ElementsAre("127.0.0.1"));
}
TEST(get_host_ipv4_addresses, empty_service) {
    EXPECT_THAT(get_host_ipv4_addresses("localhost", ""), ::testing::ElementsAre("127.0.0.1"));
}
TEST(get_host_ipv4_addresses, unknown_host) {
    EXPECT_THROW(get_host_ipv4_addresses("www.---.com", "http"), std::exception);
}
TEST(get_host_ipv4_addresses, unknown_service) {
    EXPECT_THROW(get_host_ipv4_addresses("www.boost.org", "blah"), std::exception);
}
TEST(get_host_ipv4_addresses, localhost_8080) {
    EXPECT_THAT(get_host_ipv4_addresses("localhost", "8080"), ::testing::ElementsAre("127.0.0.1"));
}


TEST(problem_95_main, output) {
    std::ostringstream oss{};
    problem_95_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Getting IPv4 addresses for host = 'localhost' and service = '8080'\n"
        "\t127.0.0.1\n"
        "Getting IPv4 addresses for host = 'www.boost.org' and service = 'http'\n"
        "\t\\d+\\.\\d+\\.\\d+\\.\\d+\n"
        "Getting IPv4 addresses for host = 'www.google.com' and service = 'https'\n"
        "\t\\d+\\.\\d+\\.\\d+\\.\\d+\n"
        "Getting IPv4 addresses for host = 'www.---.com' and service = 'http'\n"
        "\tError: resolve: No such host is known.\n"
        "Getting IPv4 addresses for host = 'www.boost.org' and service = 'blah'\n"
        "\tError: resolve: The specified class was not found.\n"
    ));
}
