#pragma once

#include <algorithm>  // for_each
#include <fmt/ostream.h>
#include <iosfwd>
#include <sstream>  // ostringstream
#include <string>
#include <type_traits>  // is_same_v


namespace tmcppc::problem_23 {
    template <typename Container>
        requires (std::is_same_v<typename Container::value_type, uint8_t>)
    std::string to_hex_string(const Container& container) {
        std::ostringstream oss{};
        std::ranges::for_each(container, [&oss](auto c) {
            fmt::print(oss, "{:02x}", static_cast<uint16_t>(c));
        });
        return oss.str();
    }
}  // namespace tmcppc::problem_23


void problem_23_main(std::ostream& os);
