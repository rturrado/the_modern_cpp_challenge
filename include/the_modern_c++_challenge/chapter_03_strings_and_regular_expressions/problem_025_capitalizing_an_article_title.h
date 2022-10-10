#pragma once

#include <iosfwd>
#include <string>
#include <string_view>


namespace tmcppc::problem_25 {
    std::string capitalize(std::string_view s);
}  // namespace tmcppc::problem_25


void problem_25_main(std::ostream& os);
