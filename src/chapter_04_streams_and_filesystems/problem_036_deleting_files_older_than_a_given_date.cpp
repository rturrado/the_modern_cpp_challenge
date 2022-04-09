#include "chapter_04_streams_and_filesystems/problem_036_deleting_files_older_than_a_given_date.h"

#include <chrono>
#include <filesystem>
#include <format>
#include <iostream>  // cout


template <typename Duration>
void delete_directory_entries_older_than(const std::filesystem::path& path, const std::chrono::file_time<Duration>& tp)
{
    namespace fs = std::filesystem;
    namespace ch = std::chrono;

    for (const fs::directory_entry& entry : fs::directory_iterator{ path })
    {
        if (fs::is_directory(entry))
        {
            delete_directory_entries_older_than(entry.path(), tp);
        }
        else if (fs::is_regular_file(entry) and fs::last_write_time(entry) < tp)
        {
            //fs::remove(entry);  // commented out so that we don't really delete the file
            
            std::cout << "\t" << entry << "\n";
        }
    }
}


// Deleting files older than a given date
//
// Write a function that, given the path to a directory and a duration,
// deletes all the entries (files or subdirectories) older than the specified duration, in a recursive manner.
// The duration can represent anything, such as days, hours, minutes, seconds, and so on,
// or a combination of that, such as one hour and twenty minutes.
// If the specified directory is itself older than the given duration, it should be deleted entirely.
void problem_36_main()
{
    namespace fs = std::filesystem;
    namespace ch = std::chrono;
    using namespace std::chrono_literals;

    const auto d1_path{ "C:\\Users\\Roberto\\Pictures" };
    const auto d2_path{ "D:\\Programacion\\vim" };

    const ch::years duration1{ 5 };
    const ch::minutes duration2{ 12h + 30min };
    
    for (const auto& path : { d1_path, d2_path })
    {
        for (const auto& tp : {
            ch::time_point<ch::file_clock>{ ch::file_clock::now() - duration1 },
            ch::time_point<ch::file_clock>{ ch::file_clock::now() - duration2 } })
        {
            std::cout << "Deleting entries older than " << std::format("{:%F %T}", tp) << " in " << path << ":\n";
            delete_directory_entries_older_than(path, tp);
        }
    }

    std::cout << "\n";
}
