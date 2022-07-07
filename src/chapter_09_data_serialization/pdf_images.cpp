#include "chapter_09_data_serialization/pdf_doc.h"
#include "chapter_09_data_serialization/pdf_images.h"
#include "chapter_09_data_serialization/pdf_layouter.h"
#include "chapter_09_data_serialization/pdf_writer_wrapper.h"
#include "env.h"

#include "rtc/string.h"

#include "PDFWriter/AbstractContentContext.h"
#include "PDFWriter/PageContentContext.h"
#include "PDFWriter/PDFPage.h"
#include "PDFWriter/PDFWriter.h"

#include <algorithm>  // any_of
#include <cctype>  // tolower
#include <filesystem>
#include <utility>  // pair
#include <vector>


namespace tmcppc::pdf {
    using ImageOptions = tmcppc::pdf_writer::ImageOptions;


    // Image list layouter
    [[nodiscard]] auto image_list_layouter::get_current_image_spacing() {
        return equals(current_y_, page_height_ - margin_top_) ? 0 : image_spacing_;
    }

    [[nodiscard]] auto image_list_layouter::image_fits_in_current_page(double image_height) {
        return less_than(image_height + get_current_image_spacing(), current_y_ - margin_bottom_);
    }

    [[nodiscard]] auto image_list_layouter::scale_image_to_fit_page(double image_width, double image_height) {
        auto ratio{ 1.0 };
        auto width_ratio{ image_width / page_width_available_ };
        auto height_ratio{ image_height / page_height_available_ };
        if (less_than(1.0, width_ratio) or less_than(1.0, height_ratio)) {
            ratio = std::max(width_ratio, height_ratio);
        }
        return std::pair<double, double>{ image_width / ratio, image_height / ratio };
    }

    [[nodiscard]] auto image_list_layouter::create_image_options_for_scaled_image(double scaled_image_width, double scaled_image_height) {
        AbstractContentContext::ImageOptions image_options{};
        image_options.transformationMethod = AbstractContentContext::eFit;
        image_options.boundingBoxWidth = scaled_image_width;
        image_options.boundingBoxHeight = scaled_image_height;
        image_options.fitProportional = true;
        return image_options;
    }

    [[nodiscard]] image_control image_list_layouter::position_image(pdf_doc* doc, const std::filesystem::path& image_file_path) {
        auto [image_width, image_height] = tmcppc::pdf_writer::get_image_dimensions(doc->get_pdf_writer(), image_file_path);
        auto [scaled_image_width, scaled_image_height] = scale_image_to_fit_page(image_width, image_height);

        if (not image_fits_in_current_page(scaled_image_height)) {
            doc->start_page(page_width_, page_height_);
            reset_cursor();
        }

        auto scaled_image_y{ current_y_ - scaled_image_height - get_current_image_spacing() };
        auto image_options{ create_image_options_for_scaled_image(scaled_image_width, scaled_image_height) };
        reset_cursor(scaled_image_y);
        
        return image_control{ margin_left_, scaled_image_y, image_options };
    }


    // Images document
    void images_doc::save_to(const std::filesystem::path& output_file_path, std::unique_ptr<layouter> layouter) {
        layouter_ = std::move(layouter);
        start_pdf(output_file_path);
        for (const auto& dir_entry : std::filesystem::directory_iterator{ input_dir_path_ }) {
            if (not is_image_file(dir_entry.path())) {
                continue;
            }
            print_image(dir_entry.path());
        }
        end_pdf();
    }

    void images_doc::start_pdf(const std::filesystem::path& output_file_path) {
        tmcppc::pdf_writer::start_pdf(pdf_writer_, output_file_path);
    }
    void images_doc::end_pdf() {
        end_page();
        tmcppc::pdf_writer::end_pdf(pdf_writer_);
    }
    void images_doc::start_page(double page_width, double page_height) {
        end_page();
        tmcppc::pdf_writer::start_page_and_page_content_context(pdf_writer_, &current_page_, &current_ctx_, page_width, page_height);
    }

    void images_doc::end_page() {
        if (current_page_ and current_ctx_) {
            tmcppc::pdf_writer::end_page_and_page_content_context(pdf_writer_, &current_page_, &current_ctx_);
        }
    }

    [[nodiscard]] bool images_doc::is_image_file(const std::filesystem::path& path) const {
        static const std::vector<std::string> valid_image_file_extensions{ ".jpg", ".jpeg", ".png", ".tiff" };
        auto file_extension{ rtc::string::to_lowercase(path.extension().string()) };
        return std::any_of(std::cbegin(valid_image_file_extensions), std::cend(valid_image_file_extensions),
            [&file_extension](auto& s) { return s == file_extension; });
    }

    void images_doc::print_image(const std::filesystem::path& image_file_path) {
        auto [x, y, image_options] = layouter_->position_image(this, image_file_path);
        tmcppc::pdf_writer::draw_image(current_ctx_, x, y, image_file_path, image_options);
    }
}  // namespace tmcppc::pdf
