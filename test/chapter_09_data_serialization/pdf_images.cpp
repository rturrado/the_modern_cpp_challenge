#include "chapter_09_data_serialization/pdf/images_doc.h"
#include "chapter_09_data_serialization/pdf/image_list_layouter.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>

using namespace tmcppc::pdf;
namespace fs = std::filesystem;


TEST(doc, save_to) {
    const auto input_dir_path{ tmcppc::env::get_instance().get_resource_folder_path() / "images" };
    const auto temp_file_path{ fs::temp_directory_path() / "images.pdf" };
    images_doc out_doc{ input_dir_path };
    out_doc.save_to(temp_file_path, std::make_unique<image_list_layouter>());
    EXPECT_TRUE(fs::exists(temp_file_path));
    EXPECT_NE(fs::file_size(temp_file_path), 0);
}
