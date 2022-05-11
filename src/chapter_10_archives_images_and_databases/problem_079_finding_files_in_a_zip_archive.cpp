#include "chapter_10_archives_images_and_databases.h"

#include "ZipArchive.h"
#include "ZipFile.h"

#include <algorithm>  // move
#include <filesystem>
#include <format>
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <regex>  // regex_match
#include <string>

namespace fs = std::filesystem;

std::vector<std::string> regex_search_in_zip_file(const fs::path& file_path, const std::regex& pattern) {
    try
    {
        if (not fs::exists(file_path))
        {
            return {};
        }

        std::vector<std::string> file_paths{};
        auto archive{ ZipFile::Open(file_path.string()) };
        for (auto i{ 0 }; i < archive->GetEntriesCount(); ++i)
        {
            auto entry{ archive->GetEntry(i) };
            if (not entry->IsDirectory())
            {
                auto& entry_file_path{ entry->GetFullName() };
                if (std::regex_match(entry_file_path, pattern))
                {
                    file_paths.push_back(entry_file_path);
                }
            }
            else
            {
                auto&& v{ regex_search_in_zip_file(file_path / entry->GetName(), pattern) };
                std::move(std::begin(v), std::end(v), std::back_inserter(file_paths));
            }
        }
        return file_paths;
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
        return {};
    }
};


// Finding files in a ZIP archive
//
// Write a program that can search for and print all the files in a ZIP archive
// whose name matches a user-provided regular expression
// (for instance, use ^.*\.jpg$ to find all files with the extension .jpg).
void problem_79_main()
{

    const std::filesystem::path input_file_path{ std::filesystem::current_path() / "res" / "problem79.zip" };
    std::string pattern_str{ R"(^.*\.jpg$)" };
    std::cout << std::format("Searching for '{}' files in '{}'...\n", pattern_str, input_file_path.string());
    for (auto&& f : regex_search_in_zip_file(input_file_path, std::regex{ pattern_str }))
    {
        std::cout << "\t"  << f << "\n";
    }
    std::cout << "\n";
}
