#include "chapter_12_networking_and_services/problem_095_finding_the_ip_address_of_a_host.h"
#include "chapter_12_networking_and_services/tcp_resolver.h"

#include <fmt/ostream.h>
#include <iostream>  // cout
#include <string>
#include <string_view>
#include <utility>  // pair
#include <vector>

#define BOOST_ASIO_STANDALONE
#include <asio.hpp>


void problem_95_main(std::ostream& os) {
    using namespace tmcppc::tcp;

    for (auto&& [host, service] : std::vector<std::pair<std::string_view, std::string_view>>{
        { "localhost", "8080" },
        { "www.boost.org", "http" },
        { "www.google.com", "https" },
        { "www.---.com", "http" },
        { "www.boost.org", "blah" } }) {

        fmt::print(os, "Getting IPv4 addresses for host = '{}' and service = '{}'\n", host, service);
        asio::io_context io_context{};
        resolver_asio resolver{ io_context };
        try {
            for (auto&& address : resolver.get_host_ipv4_addresses(host, service)) {
                fmt::print(os, "\t{}\n", address);
            }
        } catch (const std::exception& ex) {
            fmt::print(os, "\tError: {}\n", ex.what());
        }
    }

    fmt::print(os, "\n");
}


// Finding the IP address of a host
//
// Write a program that can retrieve and print the IPv4 address of a host.
// If multiple addresses are found, then all of them should be printed.
// The program should work on all platforms
void problem_95_main() {
    problem_95_main(std::cout);
}
