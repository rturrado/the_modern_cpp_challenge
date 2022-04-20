#include "chapter_04_streams_and_filesystems/problem_037_regex_find_files_in_a_directory.h"

#include <algorithm>
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <ostream>
#include <regex>  // regex_match
#include <string>
#include <vector>


std::vector<std::filesystem::directory_entry> get_directory_entries_matching(
    const std::filesystem::path& path, const std::string& pattern_str) {

    namespace fs = std::filesystem;

    std::vector<fs::directory_entry> ret{};
    std::regex pattern{ pattern_str };
    const fs::directory_options options{ fs::directory_options::skip_permission_denied };
    std::copy_if(
        fs::recursive_directory_iterator{ path, options },
        fs::recursive_directory_iterator{},
        std::back_inserter(ret),
        [&pattern](const fs::directory_entry& entry) {
            return (fs::is_regular_file(entry) and std::regex_match(entry.path().filename().string(), pattern));
        }
    );
    return ret;
}


void problem_37_main(std::ostream& os) {
    const std::string pattern_str_1{ R"(.*\.jpg$)" };  // jpg extension
    const std::string pattern_str_2{ R"(.*_.*)" };  // contains underscore
    const std::string pattern_str_3{ R"(.*[[:digit:]].*)" };  // contains a digit

    const auto path_1 = std::filesystem::current_path() / "res" / "sample_folder";
    const auto path_2 = std::filesystem::current_path() / "res" / "sample_subfolder";

    for (const auto& path : { path_1, path_2 }) {
        for (const auto& pattern_str : { pattern_str_1, pattern_str_2, pattern_str_3 }) {
            fmt::print(os, "Searching {} for entries matching pattern '{}':\n", path.generic_string(), pattern_str);
            for (auto&& entry : get_directory_entries_matching(path, pattern_str)) {
                fmt::print(os, "\t'{}'\n", entry.path().generic_string());
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
