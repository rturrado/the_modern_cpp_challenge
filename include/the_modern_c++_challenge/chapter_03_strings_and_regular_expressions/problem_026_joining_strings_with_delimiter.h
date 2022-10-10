#pragma once

#include <algorithm>  // for_each
#include <iosfwd>
#include <ranges>
#include <string>
#include <string_view>
#include <type_traits>  // is_convertible_v


namespace tmcppc::problem_26 {
    template <typename C>
        requires std::is_convertible_v<typename C::value_type, std::string_view>
    std::string join(const C& c, std::string_view delimiter) {
        std::string ret{};
        std::ranges::for_each(c, [first = true, &ret, &delimiter](std::string_view s) mutable {
            ret += (first ? "" : delimiter);
            first = false;
            ret += s;
        });
        return ret;
    }
}  // namespace tmcppc::problem_26


void problem_26_main(std::ostream& os);
