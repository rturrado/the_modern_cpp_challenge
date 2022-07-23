#pragma once

#include "env.h"

#include "rtc/console.h"
#include "rtc/filesystem.h"

#include "ZipArchive.h"
#include "ZipArchiveEntry.h"
#include "ZipFile.h"

#include <filesystem>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <istream>
#include <ostream>
#include <string>
#include <vector>


namespace tmcppc::zip {
    namespace fs = std::filesystem;

    const fs::path zip_file_extension{ "zip" };

    inline auto create_zip_file_path(const fs::path& output_root_path, const fs::path& input_path) {
        auto zip_file_name{ input_path.filename() };
        zip_file_name.replace_extension(zip_file_extension);
        return output_root_path / zip_file_name;
    }

    inline void create_directories_if_needed(const fs::path& path) {
        if (not fs::exists(path)) {
            fs::create_directories(path);
        }
    }

    inline void add_file_to_archive(const fs::path& input_path, const fs::path& zip_file_path, const std::string& password = {}) {
        ZipFile::AddEncryptedFile(zip_file_path.string(), input_path.string(), input_path.string(), password);
    }

    inline void add_directory_to_archive(const fs::path& input_path, const fs::path& zip_file_path) {
        auto archive{ ZipFile::Open(zip_file_path.generic_string()) };
        auto entry{ archive->CreateEntry(input_path.generic_string()) };
        entry->SetAttributes(ZipArchiveEntry::Attributes::Directory);
        ZipFile::SaveAndClose(archive, zip_file_path.generic_string());
    }

    inline void add_entry_to_archive(const fs::path& input_path, const fs::path& zip_file_path, const std::string& password = {}) {
        if (fs::is_regular_file(input_path)) {
            add_file_to_archive(input_path, zip_file_path, password);
        } else if (fs::is_directory(input_path)) {
            add_directory_to_archive(input_path, zip_file_path);
        }
    }

    inline void compress(
        std::ostream& os,
        const fs::path& input_path,
        const fs::path& zip_file_path,
        const std::string& password = {}) {

        fmt::print(os, "Compressing: {} -> {}\n", input_path.generic_string(), zip_file_path.generic_string());
        if (not fs::exists(input_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ input_path.generic_string() };
        }
        if (fs::exists(zip_file_path)) {
            fs::remove(zip_file_path);
        }

        try {
            if (fs::is_regular_file(input_path)) {
                fmt::print(os, "\tAdding entry: {}\n", input_path.generic_string());
                add_entry_to_archive(input_path, zip_file_path, password);
            } else if (fs::is_directory(input_path)) {
                for (auto& directory_entry : fs::recursive_directory_iterator{ input_path }) {
                    fmt::print(os, "\tAdding entry: {}\n", directory_entry.path().generic_string());
                    add_entry_to_archive(directory_entry.path(), zip_file_path, password);
                }
            }
        } catch (const std::exception&) {
            fmt::print(os, "\tRemoving archive file: {}\n", zip_file_path.generic_string());
            if (fs::exists(zip_file_path)) {
                fs::remove(zip_file_path);
            }
            throw;
        }
    }

    inline void decompress(
        std::ostream& os,
        const fs::path& zip_file_path,
        const fs::path& output_root_path,
        const std::string& password = {}) {

        fmt::print(os, "Decompressing: {} -> {}\n", zip_file_path.generic_string(), output_root_path.generic_string());
        if (not fs::exists(zip_file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ zip_file_path.generic_string() };
        }
        if (not fs::exists(output_root_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ output_root_path.generic_string() };
        }

        fmt::print(os, "\tOpening archive file: {}\n", zip_file_path.generic_string());
        auto archive{ ZipFile::Open(zip_file_path.generic_string()) };

        for (auto i{ 0 }; i < archive->GetEntriesCount(); ++i) {
            auto entry{ archive->GetEntry(i) };

            fs::path entry_file_path{ entry->GetFullName() };
            fs::path entry_relative_file_path{ entry_file_path.relative_path() };
            fs::path destination_file_path{ output_root_path / entry_relative_file_path };

            if (not entry->IsDirectory()) {
                create_directories_if_needed(destination_file_path.parent_path());

                fmt::print(os, "\tExtracting: {}\n", destination_file_path.generic_string());
                ZipFile::ExtractEncryptedFile(
                    zip_file_path.generic_string(),
                    entry_file_path.generic_string(),
                    destination_file_path.generic_string(),
                    password);
            }
        }
    }

    inline void compare_input_and_output(std::ostream& os, const fs::path& input_path, const fs::path& output_path) {
        fmt::print(os, "Checking input '{}' and output '{}' are equal\n",
            input_path.generic_string(), output_path.generic_string());
        if (not rtc::filesystem::are_filesystem_trees_equal(input_path, output_path)) {
            fmt::print(os, "\tError: Input '{}' is different than output '{}'\n",
                input_path.generic_string(), output_path.generic_string());
        } else {
            fmt::print(os, "\tOK\n");
        }
    }

    inline void remove_output(std::istream& is, std::ostream& os, const fs::path& path) {
        auto c{
            rtc::console::read_char(is, os,
                fmt::format("Are you sure you want to remove '{}' and all of its contents? [y/n] ", path.generic_string()),
                std::vector<char>{'n', 'N', 'y', 'Y'}
        )};
        if (c == 'y' or c == 'Y') {
            fs::remove_all(path);
        }
    }
}  // namespace tmcppc::zip
