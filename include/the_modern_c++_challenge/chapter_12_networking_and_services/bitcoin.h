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
        auto operator<=>(const exchange_rate& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const exchange_rate& er) {
        er.print(os);
        return os;
    }


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
        auto operator==(const exchange_rates& other) const { return data == other.data; }
        auto operator!=(const exchange_rates& other) const { return not (data == other.data); }
        auto operator<(const exchange_rates& other) const { return data < other.data; }
        auto operator>(const exchange_rates& other) const { return not ((data < other.data) or (data == other.data)); }
        auto operator<=(const exchange_rates& other) const { return not (data > other.data); }
        auto operator>=(const exchange_rates& other) const { return not (data < other.data); }
    };

    inline std::ostream& operator<<(std::ostream& os, const exchange_rates& ers) {
        ers.print(os);
        return os;
    }

}  // namespace tmcppc::bitcoin


template <>
struct fmt::formatter<tmcppc::bitcoin::exchange_rate> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::bitcoin::exchange_rate& exchange_rate, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        exchange_rate.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::bitcoin::exchange_rates> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::bitcoin::exchange_rates& exchange_rates, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        exchange_rates.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};
