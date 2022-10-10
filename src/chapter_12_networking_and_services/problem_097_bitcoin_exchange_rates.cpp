#include "chapter_12_networking_and_services/bitcoin/connection.h"
#include "chapter_12_networking_and_services/problem_097_bitcoin_exchange_rates.h"

#include <fmt/ostream.h>
#include <iostream>  // cout
#include <memory>  // make_unique


// Bitcoin exchange rates
//
// Write a program that displays Bitcoin exchange rates for the most important currencies (such as USD, EUR, or GBP).
// The exchange rates must be fetched from an online service, such as: https://blockchain.info
void problem_97_main(std::ostream& os) {
    using namespace tmcppc::bitcoin;

    bitcoin_connection connection{ std::make_unique<connector_curl>() };
    try {
        fmt::print(os, "Current bitcoin exchange rates:\n{}\n", connection.get_current_exchange_rates());
    } catch (const std::exception& ex) {
        fmt::print(os, "Error: {}\n", ex.what());
    }

    fmt::print(os, "\n");
}
