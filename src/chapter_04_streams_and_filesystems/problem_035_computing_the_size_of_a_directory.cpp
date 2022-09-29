#include "chapter_04_streams_and_filesystems/problem_035_computing_the_size_of_a_directory.h"
#include "env.h"

#include <cmath>
#include <cstdint>  // uintmax_t
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <rtc/filesystem.h>
#include <string_view>

namespace fs = std::filesystem;


namespace tmcppc::problem_35 {
    std::uintmax_t directory_size_in_bytes(const fs::path& in_dir_path, bool follow_symlinks) {
        if (not fs::exists(in_dir_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ in_dir_path.generic_string() };
        }
        if (not fs::is_directory(in_dir_path)) {
            throw rtc::filesystem::not_a_directory_error{ in_dir_path.generic_string() };
        }

        // Set up directory options
        fs::directory_options options = fs::directory_options::skip_permission_denied;
        if (follow_symlinks) {
            options |= fs::directory_options::follow_directory_symlink;
        }

        std::uintmax_t ret{ 0 };

        for (const fs::directory_entry& entry : fs::recursive_directory_iterator{ in_dir_path, options }) {
            if (not follow_symlinks and fs::is_symlink(entry)) {
                continue;
            }
            if (fs::is_regular_file(entry)) {
                ret += fs::file_size(entry);
            }
        }

        return ret;
    }


    std::string directory_size_in_bytes_to_string(uintmax_t n) {
        double d{ static_cast<double>(n) };
        std::ostringstream oss{};
        for (std::string_view unit : { "b", "KB", "MB", "GB" }) {
            if (d < 1024 or unit == "GB") {
                fmt::print(oss, "{:.0f} {}", std::floor(d), unit);
                break;
            }
            d /= 1024;
        }
        return oss.str();
    }
}  // namespace tmcppc::problem_35


void problem_35_main(std::ostream& os) {
    using namespace tmcppc::problem_35;

    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_dir_path_1{ resource_folder_path / "sample_folder" };
    const auto in_dir_path_2{ resource_folder_path / "sample_subfolder" };

    for (const auto& p : { in_dir_path_1, in_dir_path_2 }) {
        for (auto follow_symlinks : { false, true }) {
            fmt::print(os, "{}{}: ", p.generic_string(), (follow_symlinks ? " (following symlinks)" : ""));
            try {
                fmt::print(os, "{}\n", directory_size_in_bytes_to_string(directory_size_in_bytes(p, follow_symlinks)));
            } catch (const std::exception& ex) {
                fmt::print(os, "\n\tError: {}\n", ex.what());
            }
        }
    }

    fmt::print(os, "\n");
}


// Computing the size of a directory
//
// Write a function that computes the size of a directory, in bytes, recursively.
// It should be possible to indicate wheter symbolic links should be followed or not.
void problem_35_main() {
    problem_35_main(std::cout);
}
