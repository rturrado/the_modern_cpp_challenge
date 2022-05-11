#ifndef BITCOIN_H
#define BITCOIN_H

#include "rtc/pretty_print.h"

#include <format>
#include <map>
#include <ostream>
#include <string>


namespace rtc::bitcoin
{
    struct ExchangeRate
    {
        std::string symbol{};
        double fifteen_minutes{};
        double last{};
        double buy{};
        double sell{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept
        {
            os
                << indentation
                << "{ "
                << std::format("symbol: {}, 15m: {:.2f}, last: {:.2f}, buy: {:.2f}, sell: {:.2f}",
                    symbol, fifteen_minutes, last, buy, sell)
                << " }";
        }
        auto operator<=>(const ExchangeRate& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const ExchangeRate& er) { er.print(os); return os; }


    struct ExchangeRates
    {
        std::map<std::string, ExchangeRate> data{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept
        {
            os << indentation << "{\n";
            for (auto& [_, er] : data)
            {
                static size_t i{ 0 };
                bool last{ i++ == data.size() - 1 };
                os << (indentation + 1) << er << (last ? "" : ",") << "\n";
            }
            os << indentation << "}";
        }
        auto operator<=>(const ExchangeRates& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const ExchangeRates& ers) { ers.print(os); return os; }

}  // namespace rtc::bitcoin


#endif  // BITCOIN_H
