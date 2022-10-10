#pragma once

#include <chrono>
#include <filesystem>
#include <fmt/ostream.h>
#include <ostream>
#include <rtc/filesystem.h>


namespace tmcppc::problem_36 {
    template <typename Duration>
    void get_directory_entries_older_than(
        std::ostream& os, const std::filesystem::path& in_dir_path, const std::chrono::file_time<Duration>& tp,
        std::vector<std::filesystem::directory_entry>& entries) {

        namespace ch = std::chrono;
        namespace fs = std::filesystem;

        if (not fs::exists(in_dir_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ in_dir_path.generic_string() };
        }
        if (not fs::is_directory(in_dir_path)) {
            throw rtc::filesystem::not_a_directory_error{ in_dir_path.generic_string() };
        }

        for (const fs::directory_entry& entry : fs::directory_iterator{ in_dir_path }) {
            if (fs::is_directory(entry)) {
                get_directory_entries_older_than(os, entry.path(), tp, entries);
            } else if (fs::is_regular_file(entry) and fs::last_write_time(entry) < tp) {
                entries.push_back(entry);
            }
        }
    }

    template <typename Duration>
    void delete_directory_entries_older_than(
        std::ostream& os, const std::filesystem::path& in_dir_path, const std::chrono::file_time<Duration>& tp) {

        std::vector<std::filesystem::directory_entry> entries{};
        get_directory_entries_older_than(os, in_dir_path, tp, entries);
        std::ranges::sort(entries);
        for (const auto& entry : entries) {
            //fs::remove(entry);  // commented out so that we don't really delete the file

            fmt::print(os, "\t'{}'\n", entry.path().generic_string());
        }
    }
}  // namespace tmcppc::problem_36

void problem_36_main(std::ostream& os);
