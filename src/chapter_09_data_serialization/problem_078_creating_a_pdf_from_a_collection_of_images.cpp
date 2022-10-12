#include "chapter_09_data_serialization/pdf/images_doc.h"
#include "chapter_09_data_serialization/pdf/image_list_layouter.h"
#include "chapter_09_data_serialization/problem_078_creating_a_pdf_from_a_collection_of_images.h"

#include <exception>
#include <filesystem>
#include <fmt/ostream.h>


// Creating a PDF from a collection of images
//
// Write a program that can create a PDF document that contains images from a user-specified directory.
// The images must be displayed one after another.
// If an image does not fit on the remainder of a page, it must be placed on the next page.
void problem_78_main(std::ostream& os) {
    using namespace tmcppc::pdf;

    const auto input_dir_path{ tmcppc::env::get_instance().get_resource_folder_path() / "images" };
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_images.pdf" };

    try {
        images_doc out_doc{ input_dir_path };
        fmt::print(os, "Writing PDF out to: {}\n\n", temp_file_path.generic_string());
        out_doc.save_to(temp_file_path, std::make_unique<image_list_layouter>());
    } catch (const std::exception& err) {
        fmt::print(os, "Error: {}\n\n", err.what());
    }
}
