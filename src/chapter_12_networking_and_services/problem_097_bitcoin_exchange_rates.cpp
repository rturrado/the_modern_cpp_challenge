#include "chapter_12_networking_and_services/bitcoin.h"
#include "chapter_12_networking_and_services/json_bitcoin.h"
#include "chapter_12_networking_and_services/problem_097_bitcoin_exchange_rates.h"

#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>
#include <sstream>  // ostringstream
#include <string>
#include <string_view>

#include "curl_easy.h"


auto get_current_exchange_rates() {
    const std::string_view bitcoin_service_url{ "https://blockchain.info/ticker" };

    std::ostringstream oss{};
    curl::curl_ios<std::ostringstream> writer{ oss };
    curl::curl_easy easy{ writer };

    easy.add<CURLOPT_URL>(bitcoin_service_url.data());
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    easy.perform();

    nlohmann::json j = nlohmann::json::parse(oss.str());
    return tmcppc::bitcoin::exchange_rates{ j };
}


void problem_97_main(std::ostream& os) {
    try {
        fmt::print(os, "Current bitcoin exchange rates:\n{}\n", get_current_exchange_rates());
    } catch (const std::exception& ex) {
        fmt::print(os, "Error: {}\n", ex.what());
    }

    fmt::print(os, "\n");
}


// Bitcoin exchange rates
//
// Write a program that displays Bitcoin exchange rates for the most important currencies (such as USD, EUR, or GBP).
// The exchange rates must be fetched from an online service, such as: https://blockchain.info
void problem_97_main() {
    problem_97_main(std::cout);
}
