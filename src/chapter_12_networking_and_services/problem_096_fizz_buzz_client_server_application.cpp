#include "Chapter12_NetworkingAndServices.h"

#include <array>
#include <format>
#include <future>
#include <memory>  // make_shared
#include <iostream>  // cout
#include <string>  // getline
#include <string_view>
#include <system_error>  // errc

#define BOOST_ASIO_STANDALONE
#include <boost/system/error_code.hpp>
#include <boost_asio/asio/include/asio.hpp>


std::string remove_newline(std::string_view text)
{
    if (text.size() > 0 and text.ends_with('\n'))
    {
        text.remove_suffix(1);
    }
    return std::string{ text };
}


std::string read_line(asio::ip::tcp::socket& socket)
{
    std::string ret{};
    asio::error_code ec{};
    auto length{ asio::read_until(socket, asio::dynamic_buffer(ret), '\n', ec) };
    if (ec) {
        std::cout << std::format("Error: reading: {}", ec.message());
    }
    else {
        ret = remove_newline({ ret.data(), length});
    }
    return ret;
}


void write_line(asio::ip::tcp::socket& socket, const std::string& message)
{
    asio::error_code ec{};
    asio::write(socket, asio::buffer(message + "\n"), ec);
    if (ec) {
        std::cout << std::format("Error: writing: {}", ec.message());
    }
}


class server
{
public:
    server(asio::io_context& io_context, const asio::ip::tcp::endpoint& endpoint)
        : socket_{ io_context }, acceptor_{ io_context, endpoint }
    {}

    void run()
    {
        std::cout << "[server] Starting\n";
        accept();
        for (;;)
        {
            auto request_str{ read_line(socket_) };
            if (request_str == "quit") {
                break;
            }
            auto request_number{ std::atoi(request_str.c_str()) };
            auto response_str{ fizzbuzz(request_number) };
            write_line(socket_, response_str);
        }
        std::cout << "[server] Exiting\n";
    }

private:
    void accept()
    {
        acceptor_.accept(socket_);
    }

    std::string fizzbuzz(size_t number)
    {
        std::string ret{};
        if (number % 3 == 0 and number % 5 == 0) { ret = "fizz-buzz"; }
        else if (number % 3 == 0) { ret = "fizz"; }
        else if (number % 5 == 0) { ret = "buzz"; }
        else { ret = std::to_string(number); }
        return ret;
    }

private:
    asio::ip::tcp::socket socket_;
    asio::ip::tcp::acceptor acceptor_;
};


class client
{
public:
    client(asio::io_context& io_context, const asio::ip::tcp::endpoint& endpoint)
        : socket_{ io_context }, endpoint_{ endpoint }
    {}

    void run()
    {
        std::cout << "[client] Starting\n";
        connect(endpoint_);
        for (;;)
        {
            auto request_str{ read_from_console() };
            std::cout << std::format("[client] Says '{}'\n", request_str);
            write_line(socket_, request_str);
            if (request_str == "quit") {
                break;
            }
            auto response_str{ read_line(socket_) };
            std::cout << std::format("[server] Says '{}'\n", response_str);
        }
        std::cout << "[client] Exiting\n";
    }

private:
    void connect(const asio::ip::tcp::endpoint& endpoint)
    {
        socket_.connect(endpoint);
    }

    std::string read_from_console()
    {
        std::string ret{};

        for (;;)
        {
            std::cout << "[client] Please enter a number between 1 and 99 ('quit' to finish the game): ";

            std::getline(std::cin, ret);
            if (ret == "quit") {
                break;
            }

            size_t number{};
            auto [ptr, ec] = std::from_chars(ret.data(), ret.data() + ret.size(), number);
            if (ec == std::errc{} and 1 <= number and number <= 99) {
                break;
            }
            else {
                std::cout << "[client] Error: invalid input\n";
                continue;
            }
        }

        return ret;
    }

private:
    asio::ip::tcp::socket socket_;
    asio::ip::tcp::endpoint endpoint_;
};


// Write a client-server application that can be used for playing the Fizz-Buzz game.
// The client sends numbers to the server that answers back with fizz, buzz, fizz-buzz, or the number itself, according to the game rules.
// Communication between the client and the server must be done over TCP.
// The server should run indefinitely.
// The client should run as long as the user enters numbers between 1 and 99.
//
// Fizz-Buzz is a game for children, intented to teach them arithmetic division.
// A player must say a number and another player should answer with:
//   - Fizz, if the number is divisible by 3.
//   - Buzz, if the number is divisible by 5.
//   - Fizz-buzz, if the number is divisible by both 3 and 5.
//   - The number itself in other cases.
void problem_96_main()
{
    asio::io_context io{};
    asio::ip::tcp::endpoint ep{ asio::ip::make_address("127.0.0.1"), 5555 };
    server s{ io, ep };
    client c{ io, ep };
    auto server_future = std::async(std::launch::async, [&s]() { return s.run(); });
    auto client_future = std::async(std::launch::async, [&c]() { return c.run(); });

    client_future.get();
    server_future.get();

    std::cout << "\n";
}
