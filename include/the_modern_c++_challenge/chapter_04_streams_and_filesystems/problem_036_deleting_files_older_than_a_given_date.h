#pragma once

#include <chrono>
#include <filesystem>
#include <ostream>


template <typename Duration>
void delete_directory_entries_older_than(
    std::ostream& os, const std::filesystem::path& path, const std::chrono::file_time<Duration>& tp) {

    namespace fs = std::filesystem;
    namespace ch = std::chrono;

    for (const fs::directory_entry& entry : fs::directory_iterator{ path }) {
        if (fs::is_directory(entry)) {
            delete_directory_entries_older_than(os, entry.path(), tp);
        }
        else if (fs::is_regular_file(entry) and fs::last_write_time(entry) < tp) {
            //fs::remove(entry);  // commented out so that we don't really delete the file

            os << "\t'" << entry.path().generic_string() << "'\n";
        }
    }
}

void problem_36_main(std::ostream& os);
void problem_36_main();
