#pragma once

#include <iosfwd>
#include <regex>
#include <string>
#include <vector>


namespace tmcppc::problem_29 {
    inline const std::regex pattern{ R"([[:upper:]]{3}-[[:upper:]]{2} [[:digit:]]{3,4})" };

    bool validate_license_plate(const std::string& s);

    std::vector<std::string> extract_all_license_plates(const std::string& s);
}  // namespace tmcppc::problem_29


void problem_29_main(std::ostream& os);
void problem_29_main();
