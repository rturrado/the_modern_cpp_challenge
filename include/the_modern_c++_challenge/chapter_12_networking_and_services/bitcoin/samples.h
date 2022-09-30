#pragma once

#include "../bitcoin.h"

#include <fmt/format.h>
#include <rtc/pretty_print.h>
#include <string>


namespace tmcppc::bitcoin::samples {
    namespace bc = tmcppc::bitcoin;

    static inline const bc::exchange_rate exchange_rate_eur{ "EUR", 22777.77, 22777.77, 22777.77, 22777.77 };
    static inline const bc::exchange_rate exchange_rate_gbp{ "GBP", 19210.63, 19210.63, 19210.63, 19210.63 };
    static inline const bc::exchange_rates exchange_rates_eur_gbp{ .data = {
        { "EUR" , bc::exchange_rate{ "EUR", 22777.77, 22777.77, 22777.77, 22777.77 } },
        { "GBP" , bc::exchange_rate{ "GBP", 19210.63, 19210.63, 19210.63, 19210.63 } }
    } };
    static inline const bc::exchange_rates exchange_rates_eur_usd{ .data = {
        { "EUR" , bc::exchange_rate{ "EUR", 22777.77, 22777.77, 22777.77, 22777.77 } },
        { "USD" , bc::exchange_rate{ "USD", 23187.23, 23187.23, 23187.23, 23187.23 } }
    } };
    static inline const bc::exchange_rates exchange_rates_eur_gbp_usd{ .data = {
        { "EUR" , bc::exchange_rate{ "EUR", 22777.77, 22777.77, 22777.77, 22777.77 } },
        { "GBP" , bc::exchange_rate{ "GBP", 19210.63, 19210.63, 19210.63, 19210.63 } },
        { "USD" , bc::exchange_rate{ "USD", 23187.23, 23187.23, 23187.23, 23187.23 } }
    } };

    static inline const std::string exchange_rate_eur_output{
        "{ symbol: EUR, 15m: 22777.77, last: 22777.77, buy: 22777.77, sell: 22777.77 }"
    };
    static inline const std::string exchange_rates_eur_gbp_output{
        fmt::format(
            "{1}\n"
            "{0}{1} symbol: EUR, 15m: 22777.77, last: 22777.77, buy: 22777.77, sell: 22777.77 {2},\n"
            "{0}{1} symbol: GBP, 15m: 19210.63, last: 19210.63, buy: 19210.63, sell: 19210.63 {2}\n"
            "{2}",
            rtc::pretty_print::default_indentation_value, '{', '}'
        )
    };
}  // namespace tmcppc::bitcoin::samples
