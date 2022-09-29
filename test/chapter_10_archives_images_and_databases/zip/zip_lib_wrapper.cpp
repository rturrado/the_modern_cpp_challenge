#include "chapter_10_archives_images_and_databases/zip/zip_lib_wrapper.h"
#include "env.h"

#include <filesystem>
#include <gtest/gtest.h>
#include <rtc/filesystem.h>
#include <sstream>  // ostringstream

namespace fs = std::filesystem;
using namespace tmcppc::zip;


TEST(create_zip_file_path, file_stem_has_no_extension) {
    auto file_root_path{ fs::temp_directory_path() };
    auto input_file_stem{ "test_file_stem_had_no_extension" };
    auto output_file_stem{ "test_file_stem_had_no_extension.zip" };
    auto ret{ create_zip_file_path(file_root_path, input_file_stem) };
    EXPECT_EQ(ret, fs::path{ file_root_path / output_file_stem });
}
TEST(create_zip_file_path, file_stem_has_txt_extension) {
    auto file_root_path{ fs::temp_directory_path() };
    auto input_file_stem{ "test_file_stem_had_txt_extension.txt" };
    auto output_file_stem{ "test_file_stem_had_txt_extension.zip" };
    auto ret{ create_zip_file_path(file_root_path, input_file_stem) };
    EXPECT_EQ(ret, fs::path{ file_root_path / output_file_stem });
}
TEST(create_zip_file_path, file_stem_has_zip_extension) {
    auto file_root_path{ fs::temp_directory_path() };
    auto file_stem{ "test_file_stem_had_zip_extension.zip" };
    auto ret{ create_zip_file_path(file_root_path, file_stem) };
    EXPECT_EQ(ret, fs::path{ file_root_path / file_stem });
}

TEST(zip_compress, input_path_does_not_exist) {
    std::ostringstream oss{};
    EXPECT_THROW(tmcppc::zip::compress(oss, {}, {}), rtc::filesystem::file_path_does_not_exist_error);
}
TEST(zip_compress, empty_folder) {
    std::ostringstream oss{};
    const auto input_path{ fs::temp_directory_path() / "sample_empty_folder" };
    fs::remove_all(input_path);
    fs::create_directories(input_path);
    const auto zip_file_path{ create_zip_file_path(fs::temp_directory_path(), input_path) };
    tmcppc::zip::compress(oss, input_path, zip_file_path);
    EXPECT_FALSE(fs::exists(zip_file_path));
}

TEST(zip_decompress, zip_file_path_does_not_exist) {
    std::ostringstream oss{};
    const auto output_root_path{ fs::temp_directory_path() };
    EXPECT_THROW(tmcppc::zip::decompress(oss, {}, output_root_path), rtc::filesystem::file_path_does_not_exist_error);
}
TEST(zip_decompress, output_root_path_does_not_exist) {
    std::ostringstream oss{};
    const auto zip_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_folder.zip" };
    EXPECT_THROW(tmcppc::zip::decompress(oss, zip_file_path, {}), rtc::filesystem::file_path_does_not_exist_error);
}

TEST(zip_compress_decompress, non_empty_folder) {
    std::ostringstream oss{};
    const auto input_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_folder" };
    const auto output_root_path{ fs::temp_directory_path() };
    const auto output_path{ output_root_path / input_path.filename() };
    const auto zip_file_path{ create_zip_file_path(fs::temp_directory_path(), input_path) };
    tmcppc::zip::compress(oss, input_path, zip_file_path);
    tmcppc::zip::decompress(oss, zip_file_path, output_root_path);
    EXPECT_TRUE(rtc::filesystem::are_filesystem_entries_equal(input_path, output_path));
}
