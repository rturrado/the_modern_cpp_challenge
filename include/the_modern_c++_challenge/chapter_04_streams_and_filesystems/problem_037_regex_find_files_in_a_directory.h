#pragma once

#include <filesystem>
#include <iosfwd>
#include <string>
#include <vector>


namespace tmcppc::problem_37 {
    std::vector<std::filesystem::directory_entry> get_directory_entries_matching(
        const std::filesystem::path& path, const std::string& pattern_str);
}  // namespace tmcppc::problem_37


void problem_37_main(std::ostream& os);
