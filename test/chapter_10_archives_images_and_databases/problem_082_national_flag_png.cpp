#include "chapter_10_archives_images_and_databases/png/png_writer_wrapper.h"
#include "chapter_10_archives_images_and_databases/problem_082_national_flag_png.h"
#include "env.h"

#include "metric.h"
#include "rgba_image.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <filesystem>

using namespace tmcppc::png;
using namespace tmcppc::problem_82;
namespace fs = std::filesystem;


TEST(paint_romania_flag, png_output) {
    const auto master_image_file_path{ tmcppc::env::get_instance().get_resource_folder_path()
        / "images" / "masters" / "romania_flag.png" };
    const auto image_file_path{ create_png_file_path(std::filesystem::temp_directory_path(), "test_paint_romania_flag") };
    {
        png_writer png_writer(300, 200, 0.0, image_file_path);
        paint_romania_flag(png_writer);
    }
    EXPECT_TRUE(fs::exists(image_file_path));
    EXPECT_FALSE(fs::is_empty(image_file_path));
    const auto decoded_output_image{ pdiff::read_from_file(image_file_path.string()) };
    const auto decoded_master_image{ pdiff::read_from_file(master_image_file_path.string()) };
    EXPECT_TRUE(pdiff::yee_compare(*decoded_output_image, *decoded_master_image));
}

TEST(problem_82_main, ostream_output) {
    std::ostringstream oss{};
    problem_82_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("Creating .*/romania_flag.png...\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
