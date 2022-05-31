#include "chapter_04_streams_and_filesystems/problem_036_deleting_files_older_than_a_given_date.h"

#include <chrono>
#include <filesystem>
#include <fmt/ostream.h>
#include <format>
#include <iostream>  // cout
#include <ostream>


void problem_36_main(std::ostream& os) {
    namespace fs = std::filesystem;
    namespace ch = std::chrono;
    using namespace std::chrono_literals;

    const auto d1_path = std::filesystem::current_path() / "res" / "sample_folder";
    const auto d2_path = std::filesystem::current_path() / "res" / "sample_subfolder";

    const ch::years duration1{ 500 };
    const ch::milliseconds duration2{ 5 };

    for (const auto& path : { d1_path, d2_path }) {
        for (const auto& tp : {
            ch::time_point<ch::file_clock>{ ch::file_clock::now() - duration1 },
            ch::time_point<ch::file_clock>{ ch::file_clock::now() - duration2 } }) {

            fmt::print(os, "(Not) deleting entries older than {} in '{}':\n", std::format("{:%F %T}", tp), path.generic_string());
            delete_directory_entries_older_than(os, path, tp);
        }
    }

    fmt::print(os, "\n");
}


// Deleting files older than a given date
//
// Write a function that, given the path to a directory and a duration,
// deletes all the entries (files or subdirectories) older than the specified duration, in a recursive manner.
// The duration can represent anything, such as days, hours, minutes, seconds, and so on,
// or a combination of that, such as one hour and twenty minutes.
// If the specified directory is itself older than the given duration, it should be deleted entirely.
void problem_36_main() {
    problem_36_main(std::cout);
}
