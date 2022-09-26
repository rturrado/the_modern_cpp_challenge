#pragma once

#include "rtc/filesystem.h"

#include "fmt/ostream.h"

#include <algorithm>  // sort
#include <chrono>
#include <filesystem>
#include <ostream>


namespace tmcppc::problem_36 {
    template <typename Duration>
    void delete_directory_entries_older_than(
        std::ostream& os, const std::filesystem::path& in_dir_path, const std::chrono::file_time<Duration>& tp,
        std::vector<std::filesystem::directory_entry>& entries) {

        namespace fs = std::filesystem;
        namespace ch = std::chrono;

        if (not fs::exists(in_dir_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ in_dir_path.generic_string() };
        }
        if (not fs::is_directory(in_dir_path)) {
            throw rtc::filesystem::not_a_directory_error{ in_dir_path.generic_string() };
        }

        for (const fs::directory_entry& entry : fs::directory_iterator{ in_dir_path }) {
            if (fs::is_directory(entry)) {
                delete_directory_entries_older_than(os, entry.path(), tp, entries);
            } else if (fs::is_regular_file(entry) and fs::last_write_time(entry) < tp) {
                //fs::remove(entry);  // commented out so that we don't really delete the file

                entries.push_back(entry);
            }
        }
        std::ranges::sort(entries);
        for (const auto& entry : entries) {
            fmt::print(os, "\t'{}'\n", entry.path().generic_string());
        }
    }

    template <typename Duration>
    void delete_directory_entries_older_than(
        std::ostream& os, const std::filesystem::path& in_dir_path, const std::chrono::file_time<Duration>& tp) {

        std::vector<std::filesystem::directory_entry> entries{};
        delete_directory_entries_older_than(os, in_dir_path, tp, entries);
    }
}  // namespace tmcppc::problem_36

void problem_36_main(std::ostream& os);
void problem_36_main();
