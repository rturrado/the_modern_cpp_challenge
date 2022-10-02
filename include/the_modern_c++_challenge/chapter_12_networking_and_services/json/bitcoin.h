#pragma once

#include "../bitcoin.h"

#include <map>
#include <nlohmann/json.hpp>
#include <string>


namespace tmcppc::bitcoin {
    inline void from_json(const nlohmann::json& j, exchange_rate& er) {
        j.at("symbol").get_to(er.symbol);
        j.at("15m").get_to(er.fifteen_minutes);
        j.at("last").get_to(er.last);
        j.at("buy").get_to(er.buy);
        j.at("sell").get_to(er.sell);
    }

    inline void from_json(const nlohmann::json& j, exchange_rates& ers) {
        ers.data = j.get<std::map<std::string, exchange_rate>>();
    }
}  // namespace tmcppc::bitcoin
