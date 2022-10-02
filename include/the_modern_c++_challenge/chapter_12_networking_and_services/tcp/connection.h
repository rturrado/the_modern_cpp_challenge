#pragma once

#include <string>
#include <string_view>
#include <system_error>  // error_code

#define BOOST_ASIO_STANDALONE
#include <asio.hpp>
#include <boost/system/error_code.hpp>


namespace tmcppc::tcp {
    struct connector {
        virtual ~connector() = default;

        virtual void accept() = 0;
        virtual void connect() = 0;

        virtual void write(const std::string& message, std::error_code& ec) = 0;
        [[nodiscard]] virtual size_t read_until(std::string& data, std::string_view delimiter, std::error_code& ec) = 0;
    };


    class connector_asio : public connector {
    public:
        ~connector_asio() override = default;

        void write(const std::string& message, std::error_code& ec) override {
            asio::write(socket_, asio::buffer(message), ec);
        }
        [[nodiscard]] size_t read_until(std::string& data, std::string_view delimiter, std::error_code& ec) override {
            return asio::read_until(socket_, asio::dynamic_buffer(data), delimiter, ec);
        }
    protected:
        connector_asio(asio::io_context& io_context, const asio::ip::tcp::endpoint& endpoint)
            : socket_{ io_context }
            , endpoint_{ endpoint }
        {}

        asio::ip::tcp::socket socket_;
        asio::ip::tcp::endpoint endpoint_;
    };


    class connector_server_asio : public connector_asio {
    public:
        connector_server_asio(asio::io_context& io_context, const asio::ip::tcp::endpoint& endpoint)
            : connector_asio{ io_context, endpoint }
            , acceptor_{ io_context, endpoint }
        {}

        void accept() override {
            acceptor_.accept(socket_);
        }
    private:
        void connect() override {}

        asio::ip::tcp::acceptor acceptor_;
    };


    class connector_client_asio : public connector_asio {
    public:
        connector_client_asio(asio::io_context& io_context, const asio::ip::tcp::endpoint& endpoint)
            : connector_asio{ io_context, endpoint }
        {}

        void connect() override {
            socket_.connect(endpoint_);
        }
    private:
        void accept() override {}
    };
}  // namespace tmcppc::tcp
