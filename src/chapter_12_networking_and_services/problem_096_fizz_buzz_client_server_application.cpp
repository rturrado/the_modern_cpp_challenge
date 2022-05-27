#include "chapter_12_networking_and_services/problem_096_fizz_buzz_client_server_application.h"

#include <array>
#include <fmt/ostream.h>
#include <future>
#include <memory>  // make_shared
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>
#include <string>  // getline
#include <string_view>
#include <system_error>  // errc

#define BOOST_ASIO_STANDALONE
#include <boost/system/error_code.hpp>
#include <asio.hpp>


std::string remove_newline(std::string_view text) {
    if (text.size() > 0 and text.ends_with('\n')) {
        text.remove_suffix(1);
    }
    return std::string{ text };
}


std::string read_line(std::ostream& os, asio::ip::tcp::socket& socket) {
    std::string ret{};
    asio::error_code ec{};
    auto length{ asio::read_until(socket, asio::dynamic_buffer(ret), '\n', ec) };
    if (ec) {
        fmt::print(os, "Error: reading: {}", ec.message());
    } else {
        ret = remove_newline({ ret.data(), length});
    }
    return ret;
}


void write_line(std::ostream& os, asio::ip::tcp::socket& socket, const std::string& message) {
    asio::error_code ec{};
    asio::write(socket, asio::buffer(message + "\n"), ec);
    if (ec) {
        fmt::print(os, "Error: writing: {}", ec.message());
    }
}


class server {
public:
    server(std::ostream& os, asio::io_context& io_context, const asio::ip::tcp::endpoint& endpoint)
        : os_{ os }
        , socket_{ io_context }
        , acceptor_{ io_context, endpoint }
    {}

    void run() {
        fmt::print(os_, "[server] Starting\n");
        accept();
        for (;;) {
            auto request_str{ read_line(os_, socket_) };
            if (request_str == "quit") {
                break;
            }
            auto request_number{ std::atoi(request_str.c_str()) };
            auto response_str{ fizzbuzz(request_number) };
            write_line(os_, socket_, response_str);
        }
        fmt::print(os_, "[server] Exiting\n");
    }

private:
    void accept() {
        acceptor_.accept(socket_);
    }

    std::string fizzbuzz(size_t number) {
        std::string ret{};
        if (number % 3 == 0 and number % 5 == 0) { ret = "fizz-buzz"; }
        else if (number % 3 == 0) { ret = "fizz"; }
        else if (number % 5 == 0) { ret = "buzz"; }
        else { ret = std::to_string(number); }
        return ret;
    }

private:
    std::ostream& os_;
    asio::ip::tcp::socket socket_;
    asio::ip::tcp::acceptor acceptor_;
};


class client {
public:
    client(std::istream& is, std::ostream& os, asio::io_context& io_context, const asio::ip::tcp::endpoint& endpoint)
        : is_{ is }
        , os_{ os }
        , socket_ {io_context }
        , endpoint_{ endpoint }
    {}

    void run() {
        fmt::print(os_, "[client] Starting\n");
        connect(endpoint_);
        for (;;) {
            auto request_str{ read_from_console() };
            fmt::print(os_, "[client] Says '{}'\n", request_str);
            write_line(os_, socket_, request_str);
            if (request_str == "quit") {
                break;
            }
            auto response_str{ read_line(os_, socket_) };
            fmt::print(os_, "[server] Says '{}'\n", response_str);
        }
        fmt::print(os_, "[client] Exiting\n");
    }

private:
    void connect(const asio::ip::tcp::endpoint& endpoint) {
        socket_.connect(endpoint);
    }

    std::string read_from_console() {
        std::string ret{};

        for (;;) {
            fmt::print(os_, "[client] Please enter a number between 1 and 99 ('quit' to finish the game): ");

            std::getline(is_, ret);
            if (ret == "quit") {
                break;
            }

            size_t number{};
            auto [ptr, ec] = std::from_chars(ret.data(), ret.data() + ret.size(), number);
            if (ec == std::errc{} and 1 <= number and number <= 99) {
                break;
            } else {
                fmt::print(os_, "[client] Error: invalid input\n");
                continue;
            }
        }

        return ret;
    }

private:
    std::istream& is_;
    std::ostream& os_;
    asio::ip::tcp::socket socket_;
    asio::ip::tcp::endpoint endpoint_;
};


void problem_96_main(std::istream& is, std::ostream& os) {
    asio::io_context io{};
    asio::ip::tcp::endpoint ep{ asio::ip::make_address("127.0.0.1"), 5555 };
    server s{ os, io, ep };
    client c{ is, os, io, ep };
    auto server_future = std::async(std::launch::async, [&s]() { return s.run(); });
    auto client_future = std::async(std::launch::async, [&c]() { return c.run(); });

    client_future.get();
    server_future.get();

    fmt::print(os, "\n");
}


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
void problem_96_main() {
    problem_96_main(std::cin, std::cout);
}
