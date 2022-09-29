#include "chapter_09_data_serialization/pdf/images_doc.h"
#include "chapter_09_data_serialization/pdf/image_list_layouter.h"

#include <filesystem>
#include <gtest/gtest.h>

namespace fs = std::filesystem;
using namespace tmcppc::pdf;


TEST(images_doc, save_to_empty_list_of_images) {
    const auto input_dir_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" };
    const auto temp_file_path{ fs::temp_directory_path() / "test_pdf_doc_save_to_empty_list_of_images.pdf" };
    images_doc out_doc{ input_dir_path };
    out_doc.save_to(temp_file_path, std::make_unique<image_list_layouter>());
    EXPECT_TRUE(fs::exists(temp_file_path));
    EXPECT_FALSE(fs::is_empty(temp_file_path));
}

TEST(images_doc, save_to_list_of_images) {
    const auto input_dir_path{ tmcppc::env::get_instance().get_resource_folder_path() / "images" };
    const auto temp_file_path{ fs::temp_directory_path() / "test_pdf_doc_save_to_list_of_images.pdf" };
    images_doc out_doc{ input_dir_path };
    out_doc.save_to(temp_file_path, std::make_unique<image_list_layouter>());
    EXPECT_TRUE(fs::exists(temp_file_path));
    EXPECT_FALSE(fs::is_empty(temp_file_path));
}
