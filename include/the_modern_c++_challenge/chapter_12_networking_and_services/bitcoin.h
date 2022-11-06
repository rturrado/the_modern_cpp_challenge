#pragma once

#include <algorithm>  // for_each
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <map>
#include <ostream>
#include <rtc/pretty_print.h>
#include <sstream>  // ostringstream
#include <string>


namespace tmcppc::bitcoin {
    struct exchange_rate;
    struct exchange_rates;
}

// fmt formatters
template <>
struct fmt::formatter<tmcppc::bitcoin::exchange_rate> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<tmcppc::bitcoin::exchange_rates> : fmt::ostream_formatter {};


namespace tmcppc::bitcoin {
    using namespace rtc::pretty_print;

    struct exchange_rate {
        std::string symbol{};
        double fifteen_minutes{};
        double last{};
        double buy{};
        double sell{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}{} symbol: {}, 15m: {:.2f}, last: {:.2f}, buy: {:.2f}, sell: {:.2f} {}",
                indentation, '{', symbol, fifteen_minutes, last, buy, sell, '}');
        }
        friend std::ostream& operator<<(std::ostream& os, const exchange_rate& er) {
            er.print(os);
            return os;
        }
        auto operator<=>(const exchange_rate& other) const = default;
    };

    struct exchange_rates {
        std::map<std::string, exchange_rate> data{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            if (data.empty()) {
                fmt::print(os, "{}{}{}", indentation, '{', '}');
            } else {
                fmt::print(os, "{}{}", indentation, '{');
                std::ranges::for_each(data, [first = true, &os, &indentation](const auto& kvp) mutable {
                    fmt::print(os, "{}\n{}{}", first ? "" : ",", indentation + 1, kvp.second);
                    first = false;
                });
                fmt::print(os, "\n{}{}", indentation, '}');
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const exchange_rates& ers) {
            ers.print(os);
            return os;
        }
        auto operator==(const exchange_rates& other) const { return data == other.data; }
        auto operator!=(const exchange_rates& other) const { return not (data == other.data); }
        auto operator<(const exchange_rates& other) const { return data < other.data; }
        auto operator>(const exchange_rates& other) const { return not ((data < other.data) or (data == other.data)); }
        auto operator<=(const exchange_rates& other) const { return not (data > other.data); }
        auto operator>=(const exchange_rates& other) const { return not (data < other.data); }
    };
}  // namespace tmcppc::bitcoin
