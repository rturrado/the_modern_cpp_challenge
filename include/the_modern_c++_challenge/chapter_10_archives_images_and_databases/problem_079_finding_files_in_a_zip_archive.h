#pragma once

#include <filesystem>
#include <iosfwd>
#include <regex>
#include <string>
#include <vector>

namespace fs = std::filesystem;


std::vector<std::string> regex_search_in_zip_file(const fs::path& file_path, const std::regex& pattern);

void problem_79_main(std::ostream& os);
void problem_79_main();
