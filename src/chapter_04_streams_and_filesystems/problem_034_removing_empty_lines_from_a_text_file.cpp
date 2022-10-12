#include "chapter_04_streams_and_filesystems/problem_034_removing_empty_lines_from_a_text_file.h"
#include "env.h"

#include <exception>
#include <filesystem>
#include <fmt/ostream.h>
#include <ios>  // in, out
#include <regex>  // regex_search
#include <rtc/filesystem.h>

namespace fs = std::filesystem;


namespace tmcppc::problem_34 {
    fs::path remove_empty_lines(std::ostream& os, const fs::path& in_file_path) {
        if (not fs::exists(in_file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ in_file_path.generic_string() };
        }
        if (not fs::is_regular_file(in_file_path)) {
            throw rtc::filesystem::file_is_not_regular_error{ in_file_path.generic_string() };
        }
        auto out_file_path{ fs::temp_directory_path() / in_file_path.filename() };

        fmt::print(os, "Removing empty lines from input file '{}'\n", in_file_path.generic_string());
        fmt::print(os, "And writing the result to output file '{}'\n\n", out_file_path.generic_string());

        std::fstream in_f(in_file_path, std::ios::in);
        std::fstream out_f(out_file_path, std::ios::out);

        std::string line{};
        bool first{ true };  // to avoid writing a blank line at the end of the new file
        while (std::getline(in_f, line)) {
            const std::regex pattern(R"(^[[:space:]]*$)");
            if (not std::regex_search(line, pattern)) {
                fmt::print(out_f, "{}{}", (first ? "" : "\n"), line);
            }
            first = false;
        }

        in_f.close();
        out_f.close();

        return out_file_path;
    }
}  // namespace tmcppc::problem_34


// Removing empty lines from a text file
//
// Write a program that, given the path to a text file, modifies the file by removing all empty lines.
// Lines containing only whitespaces are considered empty.
void problem_34_main(std::ostream& os) {
    using namespace tmcppc::problem_34;

    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_file_path{ resource_folder_path / "problem_034_input.txt" };

    try {
        [[maybe_unused]] auto out_file_path{ remove_empty_lines(os, in_file_path) };

        //std::filesystem::rename(out_file_path, in_file_path);  // commented out so that we don't really overwrite input file
    } catch (const std::exception& ex) {
        fmt::print(os, "Error: {}\n\n", ex.what());
    }
}
