#pragma once

#include "rtc/filesystem.h"

#include "ZipArchive.h"
#include "ZipArchiveEntry.h"
#include "ZipFile.h"

#include <filesystem>
#include <fmt/ostream.h>
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

    inline void add_file_to_archive(const fs::path& zip_file_path, const fs::path& input_path, const fs::path& in_archive_path,
        const std::string& password = {}) {
        
        ZipFile::AddEncryptedFile(zip_file_path.string(), input_path.string(), in_archive_path.string(), password);
    }

    inline void add_directory_to_archive(const fs::path& zip_file_path, const fs::path& input_path) {
        auto archive{ ZipFile::Open(zip_file_path.generic_string()) };
        auto entry{ archive->CreateEntry(input_path.generic_string()) };
        entry->SetAttributes(ZipArchiveEntry::Attributes::Directory);
        ZipFile::SaveAndClose(archive, zip_file_path.generic_string());
    }

    inline void add_entry_to_archive(const fs::path& zip_file_path, const fs::path& input_path, const fs::path& in_archive_path,
        const std::string& password = {}) {

        if (fs::is_regular_file(input_path)) {
            add_file_to_archive(zip_file_path, input_path, in_archive_path, password);
        } else if (fs::is_directory(input_path)) {
            add_directory_to_archive(zip_file_path, input_path);
        }
    }

    inline auto remove_base_path(const fs::path& input_path, const fs::path& base_path) {
        fs::path ret{};
        auto ip{ std::begin(input_path) };
        for (auto bp{ base_path.begin()}; bp != base_path.end() and ip != input_path.end() and *bp == *ip; ++bp, ++ip);
        for (; ip != input_path.end(); ++ip) {
            ret /= *ip;
        }
        return ret;
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
                auto in_archive_path{ input_path.filename() };
                add_entry_to_archive(zip_file_path, input_path, in_archive_path, password);
            } else if (fs::is_directory(input_path)) {
                auto base_path{ input_path.has_relative_path() ? input_path.parent_path() : fs::path{} };
                auto options{ fs::directory_options::skip_permission_denied | fs::directory_options::follow_directory_symlink };

                for (auto& directory_entry : fs::recursive_directory_iterator{ input_path, options }) {
                    fmt::print(os, "\tAdding entry: {}\n", directory_entry.path().generic_string());
                    auto in_archive_path{ remove_base_path(directory_entry.path(), base_path) };
                    add_entry_to_archive(zip_file_path, directory_entry.path(), in_archive_path, password);
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
}  // namespace tmcppc::zip
