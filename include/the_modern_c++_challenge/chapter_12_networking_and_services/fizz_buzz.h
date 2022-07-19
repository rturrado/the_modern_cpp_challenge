#pragma once

#include <fmt/ostream.h>
#include <future>
#include <memory>  // make_shared
#include <mutex>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>
#include <string>  // getline
#include <string_view>
#include <system_error>  // errc
#include <thread>  // lock_guard

#define BOOST_ASIO_STANDALONE
#include <asio.hpp>
#include <boost/system/error_code.hpp>


namespace tmcppc::fizz_buzz {
    // fmt::ostream is not thread-safe
    // https://github.com/fmtlib/fmt/issues/1872#issuecomment-693014704
    inline static std::mutex mtx{};


    inline std::string remove_newline(std::string_view text) {
        if (text.size() > 0 and text.ends_with('\n')) {
            text.remove_suffix(1);
        }
        return std::string{ text };
    }


    inline std::string read_line(std::ostream& os, asio::ip::tcp::socket& socket) {
        std::string ret{};
        asio::error_code ec{};
        auto length{ asio::read_until(socket, asio::dynamic_buffer(ret), '\n', ec) };
        if (ec) {
            std::lock_guard<std::mutex> lock{ mtx };
            fmt::print(os, "Error: reading: {}", ec.message());
        } else {
            ret = remove_newline({ ret.data(), length });
        }
        return ret;
    }


    inline void write_line(std::ostream& os, asio::ip::tcp::socket& socket, const std::string& message) {
        asio::error_code ec{};
        asio::write(socket, asio::buffer(message + "\n"), ec);
        if (ec) {
            std::lock_guard<std::mutex> lock{ mtx };
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
            print("[server] Starting\n");
            accept();
            for (;;) {
                auto request_str{ read_line(os_, socket_) };
                if (request_str == "quit") {
                    break;
                }
                auto request_number{ std::atoi(request_str.c_str()) };
                auto response_str{ fizz_buzz(request_number) };
                write_line(os_, socket_, response_str);
            }
            print("[server] Exiting\n");
        }

    private:
        void accept() {
            acceptor_.accept(socket_);
        }

        std::string fizz_buzz(size_t number) {
            std::string ret{};
            if (number % 3 == 0 and number % 5 == 0) { ret = "fizz-buzz"; }
            else if (number % 3 == 0) { ret = "fizz"; }
            else if (number % 5 == 0) { ret = "buzz"; }
            else { ret = std::to_string(number); }
            return ret;
        }

        void print(std::string_view text) {
            std::lock_guard<std::mutex> lock{ mtx };
            fmt::print(os_, "{}", text);
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
            , socket_{ io_context }
            , endpoint_{ endpoint }
        {}

        void run() {
            print("[client] Starting\n");
            connect(endpoint_);
            for (;;) {
                auto request_str{ read_from_console() };
                print(fmt::format("[client] Says '{}'\n", request_str));
                write_line(os_, socket_, request_str);
                if (request_str == "quit") {
                    break;
                }
                auto response_str{ read_line(os_, socket_) };
                print(fmt::format("[server] Says '{}'\n", response_str));
            }
            print("[client] Exiting\n");
        }

    private:
        void connect(const asio::ip::tcp::endpoint& endpoint) {
            socket_.connect(endpoint);
        }

        std::string read_from_console() {
            std::string ret{};

            for (;;) {
                print("[client] Please enter a number between 1 and 99 ('quit' to finish the game): ");

                std::getline(is_, ret);
                if (ret == "quit") {
                    break;
                }

                size_t number{};
                auto [ptr, ec] = std::from_chars(ret.data(), ret.data() + ret.size(), number);
                if (ec == std::errc{} and 1 <= number and number <= 99) {
                    break;
                } else {
                    print("[client] Error: invalid input\n");
                    continue;
                }
            }

            return ret;
        }

        void print(std::string_view text) {
            std::lock_guard<std::mutex> lock{ mtx };
            fmt::print(os_, "{}", text);
        }

    private:
        std::istream& is_;
        std::ostream& os_;
        asio::ip::tcp::socket socket_;
        asio::ip::tcp::endpoint endpoint_;
    };
}  // namespace tmcppc::fizz_buzz
