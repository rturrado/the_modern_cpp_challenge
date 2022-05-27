#include "chapter_09_data_serialization/pdf_writer_wrapper.h"
#include "chapter_09_data_serialization/problem_078_creating_a_pdf_from_a_collection_of_images.h"

#include "rtc/filesystem.h"
#include "rtc/string.h"

#include "PDFWriter/AbstractContentContext.h"
#include "PDFWriter/PageContentContext.h"
#include "PDFWriter/PDFPage.h"
#include "PDFWriter/PDFWriter.h"

#include <algorithm>  // any_of
#include <cctype>  // tolower
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>
#include <stdexcept>  // runtime_error
#include <utility>  // pair
#include <vector>


// Constants
//
// Page
const double page_width{ 595 };
const double page_height{ 842 };
// Margins
const double margin_left{ 20 };
const double margin_right{ 20 };
const double margin_top{ 30 };
const double margin_bottom{ 30 };
// Images
const double image_spacing{ 10 };


// Page heights (double) equality and comparison
auto equals = [](double a, double b) {
    return (a - b < 0.1) and (b - a < 0.1);
};
auto less_than = [](double a, double b) {
    return (b - a > 0.1);
};


auto is_image_file(const std::filesystem::path& path) {
    const std::vector<std::string> valid_image_file_extensions{ ".jpg", ".jpeg", ".png", ".tiff" };
    auto file_extension{ rtc::string::to_lowercase(path.extension().string()) };
    return std::any_of(std::cbegin(valid_image_file_extensions), std::cend(valid_image_file_extensions),
        [&file_extension](auto& s) { return s == file_extension; });
}


auto get_current_image_spacing(const double current_y) {
    return equals(current_y, page_height - margin_top) ? 0 : image_spacing;
}


auto image_fits_in_current_page(const PDFPage* page, const double current_y, const double image_height) {
    return less_than(image_height + get_current_image_spacing(current_y), current_y - margin_bottom);
}


auto scale_image_to_fit_page(double image_width, double image_height) {
    auto ratio{ 1.0 };
    auto page_width_available{ page_width - margin_left - margin_right };
    auto page_height_available{ page_height - margin_top - margin_bottom };
    auto width_ratio{ image_width / page_width_available };
    auto height_ratio{ image_height / page_height_available };
    if (less_than(1.0, width_ratio) or less_than(1.0, height_ratio)) {
        ratio = std::max(width_ratio, height_ratio);
    }
    return std::pair<double, double>{ image_width / ratio, image_height / ratio };
}


auto create_image_options_for_scaled_image(double scaled_image_width, double scaled_image_height) {
    AbstractContentContext::ImageOptions image_options{};
    image_options.transformationMethod = AbstractContentContext::eFit;
    image_options.boundingBoxWidth = scaled_image_width;
    image_options.boundingBoxHeight = scaled_image_height;
    image_options.fitProportional = true;
    return image_options;
}


void save_folder_of_images_to_pdf(const std::filesystem::path& input_dir_path, const std::filesystem::path& output_file_path) {
    if (not std::filesystem::is_directory(input_dir_path)) {
        throw rtc::filesystem::not_a_directory_error(input_dir_path.generic_string());
    }

    PDFWriter pdf_writer{};
    PDFPage* page{};
    PageContentContext* ctx{};
    double current_y{};  // cursor height

    tmcppc::pdf_writer::start_pdf(pdf_writer, output_file_path);
    tmcppc::pdf_writer::start_page_and_page_content_context(pdf_writer, &page, &ctx, page_width, page_height);
    current_y = page_height - margin_top;

    for (const auto& dir_entry : std::filesystem::directory_iterator{ input_dir_path }) {
        if (not is_image_file(dir_entry.path())) {
            continue;
        }

        auto [image_width, image_height] = tmcppc::pdf_writer::get_image_dimensions(pdf_writer, dir_entry.path());
        auto [scaled_image_width, scaled_image_height] = scale_image_to_fit_page(image_width, image_height);
        if (not image_fits_in_current_page(page, current_y, scaled_image_height)) {
            tmcppc::pdf_writer::end_page_and_page_content_context(pdf_writer, &page, &ctx);
            tmcppc::pdf_writer::start_page_and_page_content_context(pdf_writer, &page, &ctx, page_width, page_height);
            current_y = page_height - margin_top;
        }
        auto scaled_image_y{ current_y - scaled_image_height - get_current_image_spacing(current_y) };
        auto image_options{ create_image_options_for_scaled_image(scaled_image_width, scaled_image_height) };
        tmcppc::pdf_writer::draw_image(ctx, margin_left, scaled_image_y, dir_entry.path(), image_options);
        current_y = scaled_image_y;
    }

    tmcppc::pdf_writer::end_page_and_page_content_context(pdf_writer, &page, &ctx);
    tmcppc::pdf_writer::end_pdf(pdf_writer);
}


void problem_78_main(std::ostream& os) {
    const auto input_dir_path{ std::filesystem::current_path() / "res" / "images" };
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "images.pdf" };

    try {
        fmt::print(os, "Writing PDF out to: {}\n\n", temp_file_path.generic_string());
        save_folder_of_images_to_pdf(input_dir_path, temp_file_path);
    } catch (const std::exception& err) {
        fmt::print(os, "Error: {}\n\n", err.what());
    }
}


// Creating a PDF from a collection of images
//
// Write a program that can create a PDF document that contains images from a user-specified directory.
// The images must be displayed one after another.
// If an image does not fit on the remainder of a page, it must be placed on the next page.
void problem_78_main() {
    problem_78_main(std::cout);
}
