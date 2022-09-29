#pragma once

#include "chapter_12_networking_and_services/bitcoin.h"
#include "chapter_12_networking_and_services/json/bitcoin.h"

#include <curl_easy.h>
#include <memory>  // unique_ptr
#include <sstream>  // ostringstream
#include <stdexcept>  // runtime_error
#include <string>
#include <string_view>
#include <utility>  // move


namespace tmcppc::bitcoin {
    struct bitcoin_connection_error : public std::runtime_error {
        explicit bitcoin_connection_error(std::string_view message)
            : std::runtime_error{ message.data() }
        {}
    };


    struct connector_adaptor {
        virtual ~connector_adaptor() = default;

        [[nodiscard]] virtual std::string get_current_exchange_rates() const = 0;
    };


    class connector_curl : public connector_adaptor {
    private:
        std::string_view bitcoin_service_url{ "https://blockchain.info/ticker" };
    public:
        [[nodiscard]] virtual std::string get_current_exchange_rates() const override {
            try {
                std::ostringstream oss{};
                curl::curl_ios<std::ostringstream> writer{ oss };
                curl::curl_easy easy{ writer };

                easy.add<CURLOPT_URL>(bitcoin_service_url.data());
                easy.add<CURLOPT_FOLLOWLOCATION>(1L);

                easy.perform();

                return oss.str();
            } catch (const curl::curl_easy_exception& ex) {
                throw bitcoin_connection_error{ ex.what() };
            }
        }
    };


    class bitcoin_connection {
    private:
        [[nodiscard]] exchange_rates parse_exchange_rates(const std::string& response) const {
            nlohmann::json j = nlohmann::json::parse(response);
            return exchange_rates{ j };
        }
    public:
        explicit bitcoin_connection(std::unique_ptr<connector_adaptor> connector)
            : connector_{ std::move(connector) }
        {}
        [[nodiscard]] exchange_rates get_current_exchange_rates() const {
            return parse_exchange_rates(connector_->get_current_exchange_rates());
        }
    private:
        std::unique_ptr<connector_adaptor> connector_;
    };
}  // namespace tmcppc::bitcoin
