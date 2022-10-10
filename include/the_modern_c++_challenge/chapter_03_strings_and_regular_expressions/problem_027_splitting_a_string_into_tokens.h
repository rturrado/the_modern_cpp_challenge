#pragma once

#include <iosfwd>
#include <string>
#include <vector>


namespace tmcppc::problem_27 {
    std::vector<std::string> split(const std::string& s, const std::string& delimiters);
}  // namespace tmcppc::problem_27


void problem_27_main(std::ostream& os);
