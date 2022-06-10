#pragma once

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <ostream>
#include <string>
#include <vector>


namespace tmcppc::phone {
    using numbers = std::vector<std::string>;

    enum class country_code {
        US = 1,
        Spain = 34,
        UK = 44
    };

    inline std::ostream& operator<<(std::ostream& os, const country_code& cc)
    {
        fmt::print(os, "{}", cc);
        return os;
    }
}  // namespace tmcppc::phone


template <>
struct fmt::formatter<tmcppc::phone::country_code> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::phone::country_code& cc, FormatContext& ctx) const -> decltype(ctx.out()) {
        switch (cc) {
            case tmcppc::phone::country_code::US: fmt::format_to(ctx.out(), "{}", "US"); break;
            case tmcppc::phone::country_code::Spain: fmt::format_to(ctx.out(), "{}", "Spain"); break;
            case tmcppc::phone::country_code::UK: fmt::format_to(ctx.out(), "{}", "UK"); break;
            default: fmt::format_to(ctx.out(), "{}", "Unknown country code"); break;
        }
        return ctx.out();
    }
};
