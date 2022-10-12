#pragma once

#include "console.h"

#include <iosfwd>
#include <string>


namespace tmcppc::problem_14 {
    std::string read_n_digit_isbn(std::istream& is, std::ostream& os, const tmcppc::system::console& console, size_t n);

    bool validate_10_digit_isbn(const std::string& str);
    bool validate_13_digit_isbn(const std::string& str);
}  // namespace tmcppc::problem_14


void problem_14_main(std::istream& is, std::ostream& os, const tmcppc::system::console& console);
