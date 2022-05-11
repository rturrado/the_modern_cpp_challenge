#include "Chapter12_NetworkingAndServices.h"
#include "Chapter12_NetworkingAndServices/Bitcoin.h"
#include "Chapter12_NetworkingAndServices/JsonBitcoin.h"

#include <format>
#include <iostream>  // cout
#include <sstream>  // ostringstream
#include <string>
#include <string_view>

#include "curlcpp/master/include/curl_easy.h"


auto get_current_exchange_rates()
{
    const std::string_view bitcoin_service_url{ "https://blockchain.info/ticker" };

    std::ostringstream oss{};
    curl::curl_ios<std::ostringstream> writer{ oss };
    curl::curl_easy easy{ writer };

    easy.add<CURLOPT_URL>(bitcoin_service_url.data());
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    easy.perform();

    nlohmann::json j = nlohmann::json::parse(oss.str());
    return rtc::bitcoin::ExchangeRates{ j };
}


// Bitcoin exchange rates
//
// Write a program that displays Bitcoin exchange rates for the most important currencies (such as USD, EUR, or GBP).
// The exchange rates must be fetched from an online service, such as: https://blockchain.info
void problem_97_main()
{
    try
    {
        std::cout << "Current bitcoin exchange rates:\n" << get_current_exchange_rates() << "\n";
    }
    catch (const std::exception& ex)
    {
        std::cout << std::format("Error: {}\n", ex.what());
    }

    std::cout << "\n";
}
