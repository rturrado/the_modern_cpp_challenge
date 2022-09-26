#pragma once

#include <filesystem>
#include <iosfwd>
#include <regex>
#include <string>
#include <vector>


namespace tmcppc::problem_79 {
    std::vector<std::string> regex_search_in_zip_file(std::ostream& os, const std::filesystem::path& file_path, const std::regex& pattern);
}  // namespace tmcppc::problem_79


void problem_79_main(std::ostream& os);
void problem_79_main();
