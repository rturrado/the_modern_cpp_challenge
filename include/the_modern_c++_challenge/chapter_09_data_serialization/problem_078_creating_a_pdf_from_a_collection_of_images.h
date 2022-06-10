#pragma once

#include "PDFWriter/PDFPage.h"

#include <filesystem>
#include <iosfwd>


namespace tmcppc::problem_78 {
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
    bool equals(double a, double b);
    bool less_than(double a, double b);

    bool is_image_file(const std::filesystem::path& path);

    auto get_current_image_spacing(const double current_y);

    auto image_fits_in_current_page(const PDFPage* page, const double current_y, const double image_height);

    auto scale_image_to_fit_page(double image_width, double image_height);

    auto create_image_options_for_scaled_image(double scaled_image_width, double scaled_image_height);

    void save_folder_of_images_to_pdf(
        const std::filesystem::path& input_dir_path, const std::filesystem::path& output_file_path);
}  // namespace tmcppc::problem_78


void problem_78_main(std::ostream& os);
void problem_78_main();
