#include "Chapter12_NetworkingAndServices.h"

#include <format>
#include <iostream>  // cout
#include <string>
#include <string_view>
#include <utility>  // pair
#include <vector>

#define BOOST_ASIO_STANDALONE
#include <boost_asio/asio/include/asio.hpp>

auto get_host_ipv4_addresses(std::string_view host, std::string_view service)
{
    std::vector<std::string> ret{};

    asio::io_context my_io_context;
    asio::ip::tcp::resolver resolver(my_io_context);
    auto iter{ resolver.resolve(asio::ip::tcp::v4(), host, service)};
    asio::ip::tcp::resolver::iterator end{};
    while (iter != end)
    {
        asio::ip::tcp::endpoint endpoint = *iter++;
        ret.emplace_back(endpoint.address().to_string().c_str());
    }
    return ret;
}


// Finding the IP address of a host
//
// Write a program that can retrieve and print the IPv4 address of a host.
// If multiple addresses are found, then all of them should be printed.
// The program should work on all platforms
void problem_95_main()
{
    for (auto&& [host, service] : std::vector<std::pair<std::string_view, std::string_view>>{
        { "localhost", "8080" },
        { "www.boost.org", "http" },
        { "www.google.com", "https" } })
    {
        std::cout << std::format("Getting IPv4 addresses for host = '{}' and service = '{}'\n", host, service);
        for (auto&& address : get_host_ipv4_addresses(host, service))
        {
            std::cout << std::format("\t{}\n", address);
        }
    }

    std::cout << "\n";
}
