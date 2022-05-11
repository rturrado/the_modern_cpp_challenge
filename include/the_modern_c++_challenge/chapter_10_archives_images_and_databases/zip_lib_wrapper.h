#ifndef ZIP_LIB_WRAPPER_H
#define ZIP_LIB_WRAPPER_H

#include "rtc/console.h"
#include "rtc/filesystem.h"

#include "ZipArchive.h"
#include "ZipArchiveEntry.h"
#include "ZipFile.h"

#include <filesystem>
#include <format>
#include <iostream>  // cout
#include <string>
#include <vector>


namespace rtc::zip_lib
{
    namespace fs = std::filesystem;

    const fs::path zip_file_extension{ "zip" };

    inline void create_directories_if_needed(const fs::path& path)
    {
        if (not fs::exists(path))
        {
            fs::create_directories(path);
        }
    };

    inline void add_file_to_archive(const fs::path& input_path, const fs::path& zip_file_path, const std::string& password = {})
    {
        ZipFile::AddEncryptedFile(zip_file_path.string(), input_path.string(), input_path.string(), password);
    }

    inline void add_directory_to_archive(const fs::path& input_path, const fs::path& zip_file_path)
    {
        auto archive{ ZipFile::Open(zip_file_path.generic_string()) };
        auto entry{ archive->CreateEntry(input_path.generic_string()) };
        entry->SetAttributes(ZipArchiveEntry::Attributes::Directory);
        ZipFile::SaveAndClose(archive, zip_file_path.generic_string());
    }

    inline void add_entry_to_archive(const fs::path& input_path, const fs::path& zip_file_path, const std::string& password = {})
    {
        if (fs::is_regular_file(input_path)) { add_file_to_archive(input_path, zip_file_path, password); }
        else if (fs::is_directory(input_path)) { add_directory_to_archive(input_path, zip_file_path); }
    }

    inline void compress(const fs::path& input_path, const fs::path& zip_file_path, const std::string& password = {})
    {
        std::cout << std::format("Compressing: {} -> {}\n", input_path.generic_string(), zip_file_path.generic_string());
        if (not fs::exists(input_path)) { throw rtc::filesystem::FilePathDoesNotExistError{ input_path.generic_string() }; }
        if (fs::exists(zip_file_path)) { fs::remove(zip_file_path); }

        try
        {
            if (fs::is_regular_file(input_path))
            {
                std::cout << std::format("\tAdding entry: {}\n", input_path.generic_string());
                add_entry_to_archive(input_path, zip_file_path, password);
            }
            else if (fs::is_directory(input_path))
            {
                for (auto& directory_entry : fs::recursive_directory_iterator{ input_path })
                {
                    std::cout << std::format("\tAdding entry: {}\n", directory_entry.path().generic_string());
                    add_entry_to_archive(directory_entry.path(), zip_file_path, password);
                }
            }
        }
        catch (const std::exception&)
        {
            std::cout << std::format("\tRemoving archive file: {}\n", zip_file_path.generic_string());
            if (fs::exists(zip_file_path)) { fs::remove(zip_file_path); }
            throw;
        }
    }

    inline void decompress(const fs::path& zip_file_path, const fs::path& output_root_path, const std::string& password = {})
    {
        std::cout << std::format("Decompressing: {} -> {}\n", zip_file_path.generic_string(), output_root_path.generic_string());
        if (not fs::exists(zip_file_path)) { throw rtc::filesystem::FilePathDoesNotExistError{ zip_file_path.generic_string() }; }
        if (not fs::exists(output_root_path)) { throw rtc::filesystem::FilePathDoesNotExistError{ output_root_path.generic_string() }; }

        std::cout << std::format("\tOpening archive file: {}\n", zip_file_path.generic_string());
        auto archive{ ZipFile::Open(zip_file_path.generic_string()) };

        for (auto i{ 0 }; i < archive->GetEntriesCount(); ++i)
        {
            auto entry{ archive->GetEntry(i) };

            fs::path entry_file_path{ entry->GetFullName() };
            fs::path entry_relative_file_path{ entry_file_path.relative_path() };
            fs::path destination_file_path{ output_root_path / entry_relative_file_path };

            if (not entry->IsDirectory())
            {
                create_directories_if_needed(destination_file_path.parent_path());

                std::cout << std::format("\tExtracting: {}\n", destination_file_path.generic_string());
                ZipFile::ExtractEncryptedFile(zip_file_path.generic_string(), entry_file_path.generic_string(), destination_file_path.generic_string(), password);
            }
        }
    }

    inline void compare_input_and_output(const fs::path& input_path, const fs::path& output_path)
    {
        std::cout << std::format("Checking input '{}' and output '{}' are equal\n", input_path.generic_string(), output_path.generic_string());
        if (not rtc::filesystem::are_filesystem_trees_equal(input_path, output_path))
        {
            std::cout << std::format("\tError: Input '{}' is different than output '{}'\n", input_path.generic_string(), output_path.generic_string());
        }
        else
        {
            std::cout << "\tOK\n";
        }
    }

    inline void remove_output(const fs::path& path)
    {
        auto c{
            read_char(
                std::format("Are you sure you want to remove '{}' and all its contents? [y/n] ", path.string()),
                std::vector<char>{'n', 'N', 'y', 'Y'})
        };
        if (c == 'y' or c == 'Y')
        {
            fs::remove_all(path);
        }
    }

    inline void test(const std::string& password = {})
    {
        auto create_zip_file_path = [](const fs::path& output_root_path, const fs::path& input_path)
        {
            auto zip_file_name{ input_path.filename() };
            zip_file_name.replace_extension(zip_file_extension);
            return output_root_path / zip_file_name;
        };

        const auto input_file_path{ fs::path{ "res" } / "problem80" / "file.jpg" };  // test relative paths
        const auto input_dir_path{ fs::current_path() / "res" / "problem80" / "folder" };  // and absolute paths
        const auto output_root_path{ fs::temp_directory_path() };

        for (auto&& input_path : { input_file_path, input_dir_path })
        {
            const auto output_path{ output_root_path / input_path.relative_path() };
            const auto output_relative_root_directory_path{ output_root_path / *input_path.relative_path().begin() };
            const auto zip_file_path{ create_zip_file_path(output_root_path, input_path) };

            // Input path                                c:/programming/code/c++/the_modern_c++_challenge/res/problem80/file.jpg
            // Input relative path                          programming/code/c++/the_modern_c++_challenge/res/problem80/file.jpg
            // Input file name                                                                                          file.jpg
            // Output root path                     c:/temp
            // Output path                          c:/temp/programming/code/c++/the_modern_c++_challenge/res/problem80/file.jpg
            // Output relative root directory path  c:/temp/programming
            // Zip file path                        c:/temp/                                                            file.zip

            try
            {
                compress(input_path, zip_file_path, password);
                decompress(zip_file_path, output_root_path, password);
                compare_input_and_output(input_path, output_path);
                remove_output(output_relative_root_directory_path);
            }
            catch (const std::exception& ex)
            {
                std::cout << std::format("\nError: {}\n", ex.what());
            }
            std::cout << "\n";
        }
    }
}  // namespace rtc::zip_lib


#endif  // ZIP_LIB_WRAPPER_H
