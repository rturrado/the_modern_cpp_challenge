#include "chapter_10_archives_images_and_databases/ean_13_barcode.h"
#include "chapter_10_archives_images_and_databases/ean_13_barcode_png_generator.h"
#include "chapter_10_archives_images_and_databases/problem_084_ean_13_barcode_generator.h"

#include <bitset>
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>
#include <string>


void problem_84_main(std::ostream& os) {
    auto code_png_generator{ tmcppc::ean_13::barcode_png::generator{} };
    for (auto&& code_str : { "2407014001944", "9781123123456", "5012345678900" }) {
        const auto image_file_path{ tmcppc::png::create_png_file_path(std::filesystem::temp_directory_path(), code_str) };
        fmt::print(os, "Creating {}...\n\n", image_file_path.generic_string());

        code_png_generator(tmcppc::ean_13::barcode{ code_str }, 1.0, image_file_path);
    }
}


// EAN-13 barcode generator
//
// Write a program that can generate a PNG image with an EAN-13 barcode for any international article number in version 13 of the standard.
// For simplicity, the image should only contain the barcode and can skip the EAN-13 number printed under the barcode.
void problem_84_main() {
    problem_84_main(std::cout);
}
