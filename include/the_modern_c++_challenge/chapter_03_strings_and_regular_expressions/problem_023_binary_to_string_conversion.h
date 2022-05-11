#pragma once

#include <algorithm>  // for_each
#include <fmt/ostream.h>
#include <ostream>
#include <sstream>  // ostringstream
#include <string>
#include <type_traits>  // is_same_v


template <typename Container>
requires (std::is_same_v<typename Container::value_type, uint8_t>)
std::string to_string(const Container& container) {
    std::ostringstream oss{};
    std::for_each(cbegin(container), cend(container), [&oss](auto c) {
        fmt::print(oss, "{:02x}", static_cast<uint16_t>(c));
    });
    return oss.str();
}


void problem_23_main(std::ostream& os);
void problem_23_main();
