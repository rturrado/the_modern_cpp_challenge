#include "chapter_10_archives_images_and_databases/ean_13/barcode.h"
#include "chapter_10_archives_images_and_databases/ean_13/barcode_png_generator.h"
#include "env.h"

#include "metric.h"
#include "rgba_image.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>

namespace fs = std::filesystem;


TEST(ean_13_barcode_png_generator, operator_function_call) {
    const auto master_image_file_path{ tmcppc::env::get_instance().get_resource_folder_path()
        / "images" / "masters" / "2407014001944.png" };
    const auto image_file_path{ tmcppc::png::create_png_file_path(std::filesystem::temp_directory_path(),
        "test_ean_13_barcode_png_generator_operator_function_all") };
    auto code_png_generator{ tmcppc::ean_13::barcode_png::generator{} };
    auto code_str{ "2407014001944" };
    code_png_generator(tmcppc::ean_13::barcode{ code_str }, 1.0, image_file_path);
    EXPECT_TRUE(fs::exists(image_file_path));
    EXPECT_FALSE(fs::is_empty(image_file_path));
    const auto decoded_output_image{ pdiff::read_from_file(image_file_path.string()) };
    const auto decoded_master_image{ pdiff::read_from_file(master_image_file_path.string()) };
    EXPECT_TRUE(pdiff::yee_compare(*decoded_output_image, *decoded_master_image));
}
