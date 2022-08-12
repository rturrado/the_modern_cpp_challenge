#pragma once

#include <string>
#include <string_view>
#include <system_error>  // error_code
#include <vector>

#define BOOST_ASIO_STANDALONE
#include <asio.hpp>
#include <boost/system/error_code.hpp>


namespace tmcppc::tcp {
    using ipv4_addresses = std::vector<std::string>;


    struct resolver {
        virtual ~resolver() = default;

        [[nodiscard]] virtual ipv4_addresses get_host_ipv4_addresses(std::string_view host,
            std::string_view service) const = 0;
    };


    class resolver_asio : public resolver {
    public:
        resolver_asio(asio::io_context& io_context)
            : io_context_{ io_context }
        {}

        [[nodiscard]] virtual ipv4_addresses get_host_ipv4_addresses(std::string_view host,
            std::string_view service) const override {

            ipv4_addresses ret{};

            asio::ip::tcp::resolver resolver{ io_context_ };
            auto iter{ resolver.resolve(asio::ip::tcp::v4(), host, service) };
            asio::ip::tcp::resolver::iterator end{};
            while (iter != end) {
                asio::ip::tcp::endpoint endpoint = *iter++;
                ret.emplace_back(endpoint.address().to_string().c_str());
            }
            return ret;
        }
    private:
        asio::io_context& io_context_;
    };
}  // namespace tmcppc::tcp
