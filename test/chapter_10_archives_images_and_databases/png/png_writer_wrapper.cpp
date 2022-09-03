#include "chapter_10_archives_images_and_databases/png/png_writer_wrapper.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace tmcppc::png;
namespace fs = std::filesystem;


TEST(create_png_file_path, file_stem_has_no_extension) {
    auto file_root_path{ fs::temp_directory_path() };
    auto input_file_stem{ "test_file_stem_had_no_extension" };
    auto output_file_stem{ "test_file_stem_had_no_extension.png" };
    auto ret{ create_png_file_path(file_root_path, input_file_stem) };
    EXPECT_EQ(ret, fs::path{ file_root_path / output_file_stem });
}
TEST(create_png_file_path, file_stem_has_txt_extension) {
    auto file_root_path{ fs::temp_directory_path() };
    auto input_file_stem{ "test_file_stem_had_txt_extension.txt" };
    auto output_file_stem{ "test_file_stem_had_txt_extension.png" };
    auto ret{ create_png_file_path(file_root_path, input_file_stem) };
    EXPECT_EQ(ret, fs::path{ file_root_path / output_file_stem });
}
TEST(create_png_file_path, file_stem_has_png_extension) {
    auto file_root_path{ fs::temp_directory_path() };
    auto file_stem{ "test_file_stem_had_png_extension.png" };
    auto ret{ create_png_file_path(file_root_path, file_stem) };
    EXPECT_EQ(ret, fs::path{ file_root_path / file_stem });
}
