#pragma once

#include "doc.h"
#include "env.h"
#include "layouter.h"
#include "pdf_writer_wrapper.h"

#include <algorithm>  // any_of
#include <cctype>  // tolower
#include <filesystem>
#include <PDFWriter/AbstractContentContext.h>
#include <PDFWriter/PageContentContext.h>
#include <PDFWriter/PDFPage.h>
#include <PDFWriter/PDFWriter.h>
#include <rtc/filesystem.h>
#include <rtc/string.h>
#include <utility>  // move, pair
#include <vector>


namespace tmcppc::pdf {
    class images_doc : public doc {
    public:
        explicit images_doc(const std::filesystem::path& input_dir_path) : input_dir_path_{ input_dir_path } {
            if (not std::filesystem::is_directory(input_dir_path_)) {
                throw rtc::filesystem::not_a_directory_error(input_dir_path_.generic_string());
            }
        }

        virtual void start_pdf(const std::filesystem::path& output_file_path) override {
            tmcppc::pdf_writer::start_pdf(pdf_writer_, output_file_path);
        }

        virtual void start_page(double page_width, double page_height) override {
            tmcppc::pdf_writer::start_page_and_page_content_context(pdf_writer_, &current_page_, &current_ctx_, page_width, page_height);
            page_counter_++;
        }

        virtual void end_pdf() override {
            end_page();
            tmcppc::pdf_writer::end_pdf(pdf_writer_);
        }
        virtual void end_page() override {
            if (current_page_ and current_ctx_) {
                tmcppc::pdf_writer::end_page_and_page_content_context(pdf_writer_, &current_page_, &current_ctx_);
            }
        }

        virtual void save_to(const std::filesystem::path& output_file_path, std::unique_ptr<layouter> layouter) override {
            layouter_ = std::move(layouter);
            start_pdf(output_file_path);
            start_page(layouter_->get_page_width(), layouter_->get_page_height());
            for (const auto& dir_entry : std::filesystem::directory_iterator{ input_dir_path_ }) {
                if (not is_image_file(dir_entry.path())) {
                    continue;
                }
                print_image(dir_entry.path());
            }
            end_pdf();
        }

    private:
        std::filesystem::path input_dir_path_{};

        [[nodiscard]] bool is_image_file(const std::filesystem::path& path) const {
            static const std::vector<std::string> valid_image_file_extensions{ ".jpg", ".jpeg", ".png", ".tiff" };
            auto file_extension{ rtc::string::to_lowercase(path.extension().string()) };
            return std::ranges::any_of(valid_image_file_extensions,
                [&file_extension](auto& s) { return s == file_extension; });
        }

        void print_image(const std::filesystem::path& image_file_path) {
            auto [image_width, image_height] = tmcppc::pdf_writer::get_image_dimensions(pdf_writer_, image_file_path);
            auto [x, y, image_options] = layouter_->position_image(this, image_width, image_height);
            tmcppc::pdf_writer::draw_image(current_ctx_, x, y, image_file_path, image_options);
        }
    };
}  // namespace tmcppc::pdf
