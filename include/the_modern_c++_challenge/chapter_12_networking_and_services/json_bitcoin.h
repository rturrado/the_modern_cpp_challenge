#ifndef JSON_BITCOIN_H
#define JSON_BITCOIN_H

#include "Bitcoin.h"

#include "nlohmann/json.hpp"

#include <string>
#include <map>


namespace rtc::bitcoin
{
    inline void from_json(const nlohmann::json& j, ExchangeRate& er)
    {
        j.at("symbol").get_to(er.symbol);
        j.at("15m").get_to(er.fifteen_minutes);
        j.at("last").get_to(er.last);
        j.at("buy").get_to(er.buy);
        j.at("sell").get_to(er.sell);
    }

    inline void from_json(const nlohmann::json& j, ExchangeRates& ers)
    {
        ers.data = j.get<std::map<std::string, ExchangeRate>>();
    }

}  // namespace rtc::bitcoin


#endif  // JSON_BITCOIN_H
