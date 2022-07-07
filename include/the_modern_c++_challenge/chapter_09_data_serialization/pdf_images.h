#pragma once

#include "pdf_doc.h"
#include "pdf_layouter.h"

#include "rtc/filesystem.h"

#include <filesystem>
#include <iosfwd>


namespace tmcppc::pdf {
    // Image list layouter
    class image_list_layouter : public layouter {
    public:
        [[nodiscard]] virtual image_control position_image(pdf_doc* doc, const std::filesystem::path& image_file_path) override;
        [[nodiscard]] virtual line_control position_line() override { return {}; }
        [[nodiscard]] virtual text_control position_text(pdf_doc*, const std::string&, bool, const text_alignment&) override { return {}; }
        [[nodiscard]] virtual text_control position_title(pdf_doc*, const std::string&, const text_alignment&) override { return {}; }

    private:
        [[nodiscard]] auto get_current_image_spacing();
        [[nodiscard]] auto image_fits_in_current_page(const double image_height);
        [[nodiscard]] auto scale_image_to_fit_page(double image_width, double image_height);
        [[nodiscard]] auto create_image_options_for_scaled_image(double scaled_image_width, double scaled_image_height);
    };


    // Images document
    class images_doc : public pdf_doc{
    public:
        images_doc(const std::filesystem::path& input_dir_path) : input_dir_path_{ input_dir_path } {
            if (not std::filesystem::is_directory(input_dir_path_)) {
                throw rtc::filesystem::not_a_directory_error(input_dir_path_.generic_string());
            }
        }

        virtual void save_to(const std::filesystem::path& output_file_path, std::unique_ptr<layouter> layouter) override;

        virtual void start_page(double page_width, double page_height) override;
        virtual void end_page() override;

    private:
        std::filesystem::path input_dir_path_{};

        virtual void start_pdf(const std::filesystem::path& output_file_path) override;
        virtual void end_pdf() override;

        [[nodiscard]] bool is_image_file(const std::filesystem::path& path) const;
        void print_image(const std::filesystem::path& image_file_path);
    };
}  // namespace tmcppc::pdf
