#include "chapter_04_streams_and_filesystems/problem_037_regex_find_files_in_a_directory.h"
#include "env.h"

#include <algorithm>  // copy_if, sort
#include <exception>
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <regex>  // regex_match
#include <rtc/filesystem.h>
#include <string>
#include <vector>

namespace fs = std::filesystem;


namespace tmcppc::problem_37 {
    std::vector<fs::directory_entry> get_directory_entries_matching(const fs::path& in_dir_path, const std::string& pattern_str) {
        if (not fs::exists(in_dir_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ in_dir_path.generic_string() };
        }
        if (not fs::is_directory(in_dir_path)) {
            throw rtc::filesystem::not_a_directory_error{ in_dir_path.generic_string() };
        }

        std::vector<fs::directory_entry> ret{};
        std::regex pattern{ pattern_str };
        const fs::directory_options options{ fs::directory_options::skip_permission_denied };
        std::copy_if(
            fs::recursive_directory_iterator{ in_dir_path, options },
            fs::recursive_directory_iterator{},
            std::back_inserter(ret),
            [&pattern](const fs::directory_entry& entry) {
                return (fs::is_regular_file(entry) and std::regex_match(entry.path().filename().string(), pattern));
            }
        );
        std::ranges::sort(ret);
        return ret;
    }
}  // namespace tmcppc::problem_37


void problem_37_main(std::ostream& os) {
    using namespace tmcppc::problem_37;

    const std::string pattern_str_1{ R"(.*\.jpg$)" };  // jpg extension
    const std::string pattern_str_2{ R"(.*_.*)" };  // contains underscore
    const std::string pattern_str_3{ R"(.*[[:digit:]].*)" };  // contains a digit

    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_dir_path_1{ resource_folder_path / "sample_folder" };
    const auto in_dir_path_2{ resource_folder_path / "sample_subfolder" };

    for (const auto& path : { in_dir_path_1, in_dir_path_2 }) {
        for (const auto& pattern_str : { pattern_str_1, pattern_str_2, pattern_str_3 }) {
            fmt::print(os, "Searching {} for entries matching pattern '{}':\n", path.generic_string(), pattern_str);
            try {
                for (auto&& entry : get_directory_entries_matching(path, pattern_str)) {
                    fmt::print(os, "\t'{}'\n", entry.path().generic_string());
                }
            } catch (const std::exception& ex) {
                fmt::print(os, "\n\tError: {}\n", ex.what());
            }
        }
    }

    fmt::print(os, "\n");
}


// Finding files in a directory that match a regular expression
//
// Write a function that, given the path to a directory and a regular expression,
// returns a list of all the directory entries whose names match the regular expression.
void problem_37_main() {
    problem_37_main(std::cout);
}
