#include "chapter_04_streams_and_filesystems/problem_036_deleting_files_older_than_a_given_date.h"
#include "env.h"

#include <chrono>
#include <exception>
#include <filesystem>
#include <fmt/chrono.h>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>


// Deleting files older than a given date
//
// Write a function that, given the path to a directory and a duration,
// deletes all the entries (files or subdirectories) older than the specified duration, in a recursive manner.
// The duration can represent anything, such as days, hours, minutes, seconds, and so on,
// or a combination of that, such as one hour and twenty minutes.
// If the specified directory is itself older than the given duration, it should be deleted entirely.
void problem_36_main(std::ostream& os) {
    namespace ch = std::chrono;
    namespace fs = std::filesystem;
    using namespace std::chrono_literals;
    using namespace tmcppc::problem_36;

    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_dir_path_1{ resource_folder_path / "sample_folder" };
    const auto in_dir_path_2{ resource_folder_path / "sample_subfolder" };

    const auto tp_sc_1970_jan_01{ ch::sys_days{ 1970y / ch::January / 1 } };
    const auto tp_fc_1970_jan_01{ ch::clock_cast<ch::file_clock>(ch::round<ch::milliseconds>(tp_sc_1970_jan_01)) };
    const auto tp_fc_5_ms_ago{ ch::round<ch::seconds>(ch::file_clock::now()) - ch::milliseconds{ 5 } };

    for (const auto& path : { in_dir_path_1, in_dir_path_2 }) {
        for (const auto& tp : { tp_fc_1970_jan_01, tp_fc_5_ms_ago }) {
            try {
                fmt::print(os, "(Not) deleting entries older than {:%F %T} in '{}':\n",
                    ch::clock_cast<ch::system_clock>(tp), path.generic_string());
                delete_directory_entries_older_than(os, path, tp);
            } catch (const std::exception& ex) {
                fmt::print(os, "\n\tError: {}\n", ex.what());
            }
        }
    }

    fmt::print(os, "\n");
}
