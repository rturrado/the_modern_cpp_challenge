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

    inline std::ostream& operator<<(std::ostream& os, const country_code& cc) {
        switch (cc) {
            case country_code::US: return os << fmt::format("{}", "US");
            case country_code::Spain: return os << fmt::format("{}", "Spain");
            case country_code::UK: return os << fmt::format("{}", "UK");
            default: return os << fmt::format("{}", "Unknown country code");
        }
        return os;
    }
}  // namespace tmcppc::phone


// fmt formatter
template <>
struct fmt::formatter<tmcppc::phone::country_code> : fmt::ostream_formatter {};
