#include "chapter_04_streams_and_filesystems/problem_035_computing_the_size_of_a_directory.h"

#include <cstdint>  // uintmax_t
#include <filesystem>
#include <iomanip>  // setprecision
#include <ios>  // fixed
#include <iostream>  // cout
#include <sstream>  // ostringstream
#include <string>


std::uintmax_t directory_size_b(const std::filesystem::path& p, bool follow_symlinks = false)
{
    namespace fs = std::filesystem;

    // Set up directory options
    fs::directory_options options = fs::directory_options::skip_permission_denied;
    if (follow_symlinks)
    {
        options |= fs::directory_options::follow_directory_symlink;
    }

    std::uintmax_t ret{ 0 };

    for (const fs::directory_entry& entry : fs::recursive_directory_iterator{ p, options })
    {
        if (not follow_symlinks and fs::is_symlink(entry))
        {
            continue;
        }
        if (fs::is_regular_file(entry))
        {
            ret += fs::file_size(entry);
        }
    }

    return ret;
}


std::string to_string(uintmax_t n)
{
    double d{ static_cast<double>(n) };
    std::ostringstream oss{};
    for (auto& unit : { "b", "KB", "MB", "GB" })
    {
        if (d < 1024 or unit == "GB")
        {
            oss << std::fixed << std::setprecision(2) << d << " " << unit;
            break;
        }
        d /= 1024;
    }
    return oss.str();
}


// Computing the size of a directory
//
// Write a function that computes the size of a directory, in bytes, recursively.
// It should be possible to indicate wheter symbolic links should be followed or not.
void problem_35_main()
{
    namespace fs = std::filesystem;

    const auto d1_path{ "C:\\Users\\Roberto\\Pictures" };
    const auto d2_path{ "C:\\Users\\Roberto\\.bash_history" };
    const auto d3_path{ "D:\\Programacion\\vim" };

    for (const auto& p : { d1_path, d2_path, d3_path })
    {
        for (auto follow_symlinks : { false, true })
        {
            std::cout << p << (follow_symlinks ? " (following symlinks)" : "") << ": ";
            try
            {
                std::cout << to_string(directory_size_b(p, follow_symlinks)) << "\n";
            }
            catch (const std::filesystem::filesystem_error& ex)
            {
                std::cerr << "\n\tError: " << ex.what() << '\n';
            }
        }
    }

    std::cout << "\n";
}
