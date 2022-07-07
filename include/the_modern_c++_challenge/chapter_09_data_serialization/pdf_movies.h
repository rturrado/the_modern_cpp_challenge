#pragma once

#include "movies.h"
#include "pdf_doc.h"
#include "pdf_layouter.h"

#include "PDFWriter/AbstractContentContext.h"

#include <filesystem>
#include <memory>  // unique_ptr
#include <string>


namespace tmcppc::pdf {
    // Text list layouter
    class text_list_layouter : public layouter {
    public:
        explicit text_list_layouter(int text_lines_per_page);

        [[nodiscard]] virtual image_control position_image(pdf_doc* doc, const std::filesystem::path& image_file_path) {
            return {};
        };
        [[nodiscard]] virtual line_control position_line() override;
        [[nodiscard]] virtual text_control position_text(pdf_doc* doc, const std::string& text, bool add_new_line,
            const text_alignment& alignment) override;
        [[nodiscard]] virtual text_control position_title(pdf_doc* doc, const std::string& text,
            const text_alignment& alignment) override;

    private:
        double title_font_width_{ 9 };
        double title_font_height_{ 16 };
        int text_lines_per_page_{ 40 };
        int text_line_counter_{ 0 };
        AbstractContentContext::TextOptions text_options_{ nullptr };
        AbstractContentContext::TextOptions title_text_options_{ nullptr };

        [[nodiscard]] bool text_fits_in_current_page() const;
        [[nodiscard]] AbstractContentContext::TextOptions get_text_options(pdf_doc* doc);
        [[nodiscard]] AbstractContentContext::TextOptions get_title_text_options(pdf_doc* doc);
        [[nodiscard]] double get_text_x(const std::string& text, double font_width, const text_alignment& alignment);
    };


    // Movies document
    class movies_doc : public pdf_doc {
        using catalog = tmcppc::movies::catalog;

    public:
        movies_doc(const catalog& c) : catalog_{ c } {}

        virtual void save_to(const std::filesystem::path& output_file_path, std::unique_ptr<layouter> layouter) override;

        virtual void start_page(double page_width, double page_height) override;
        virtual void end_page() override;

    private:
        catalog catalog_{};

        virtual void start_pdf(const std::filesystem::path& output_file_path) override;
        virtual void end_pdf() override;

        void print_title();
        void print_line_separator();
        void print_text_line(const std::string& text, bool add_new_line, const text_alignment& align);
    };
}  // namespace tmcppc::pdf
