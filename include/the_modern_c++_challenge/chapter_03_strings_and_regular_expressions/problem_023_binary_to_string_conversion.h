#pragma once

#include <algorithm>  // for_each
#include <iomanip>  // setfill, setw
#include <ios>  // dec, hex
#include <ostream>
#include <sstream>  // ostringstream
#include <string>
#include <type_traits>  // is_same_v


template <typename Container>
std::string to_string(const Container& container)
    requires (std::is_same_v<typename Container::value_type, uint8_t>)
{
    std::ostringstream oss{};
    std::for_each(cbegin(container), cend(container), [&oss](auto c) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(c) << std::dec; });
    return oss.str();
}


void problem_23_main(std::ostream& os);
void problem_23_main();
