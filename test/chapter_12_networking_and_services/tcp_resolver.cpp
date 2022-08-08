#include "chapter_12_networking_and_services/tcp_resolver.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exception>

#define BOOST_ASIO_STANDALONE
#include <asio.hpp>

using namespace tmcppc::tcp;


TEST(resolver_asio, DISABLED_get_host_ipv4_addresses_with_empty_host) {
    asio::io_context io_context{};
    EXPECT_THAT(
        resolver_asio{ io_context }.get_host_ipv4_addresses("", "8080"),
        ::testing::ElementsAre("127.0.0.1")
    );
}
TEST(resolver_asio, DISABLED_get_host_ipv4_addresses_with_empty_service) {
    asio::io_context io_context{};
    EXPECT_THAT(
        resolver_asio{ io_context }.get_host_ipv4_addresses("localhost", ""),
        ::testing::ElementsAre("127.0.0.1")
    );
}
TEST(resolver_asio, DISABLED_get_host_ipv4_addresses_with_unknown_host) {
    asio::io_context io_context{};
    EXPECT_THROW(
        resolver_asio{ io_context }.get_host_ipv4_addresses("www.---.com", "http"),
        std::exception
    );
}
TEST(resolver_asio, DISABLED_get_host_ipv4_addresses_with_unknown_service) {
    asio::io_context io_context{};
    EXPECT_THROW(
        resolver_asio{ io_context }.get_host_ipv4_addresses("www.boost.org", "blah"),
        std::exception
    );
}
TEST(resolver_asio, DISABLED_get_host_ipv4_addresses_with_localhost_8080) {
    asio::io_context io_context{};
    EXPECT_THAT(
        resolver_asio{ io_context }.get_host_ipv4_addresses("localhost", "8080"),
        ::testing::ElementsAre("127.0.0.1")
    );
}
