#pragma once

#include "movies.h"
#include "pdf_writer_wrapper.h"

#include "PDFWriter/AbstractContentContext.h"
#include "PDFWriter/PDFWriter.h"

#include <filesystem>
#include <memory>  // unique_ptr

class PageContentContext;


namespace tmcppc::movies::pdf {
    class doc;

    // Layouter
    class layouter {
    public:
        virtual ~layouter() = default;
        virtual void print(doc* doc, const movie& movie) = 0;

    protected:
        // Page
        double page_width{ 595 };
        double page_height{ 842 };
        // Margins
        double margin_left{ 20 };
        double margin_right{ 20 };
        double margin_top{ 30 };
        double margin_bottom{ 30 };
        // Text
        double font_width{ 8 };
        double font_height{ 14 };
        double line_spacing{ 5 };
        // Text options
        AbstractContentContext::TextOptions text_options{ nullptr, font_height, AbstractContentContext::eGray, 0 };
        // Cursor
        double current_y{};

    protected:
        void set_font(PDFWriter& pdf_writer);
    };


    // List layouter
    class list_layouter : public layouter {
    public:
        explicit list_layouter(int movies_per_page);
        virtual void print(doc* doc, const movie& movie) override;

    private:
        int movies_per_page_{};
        int page_counter_{};
        bool is_first_movie_of_page_{};

        [[nodiscard]] bool is_first_movie_of_page() const noexcept;
        [[nodiscard]] bool is_last_movie_of_page(doc* doc) const noexcept;
        void set_is_first_movie_of_page(bool flag) noexcept;
        void reset_cursor() noexcept;
        void print_title(PageContentContext* ctx);
        void print_line_separator(PageContentContext* ctx);
        void print_movie(PageContentContext* ctx, const movie& movie);
    };


    // PDF document
    class doc {
    public:
        doc(const catalog& c) : catalog_{ c } {}

        void save_to(const std::filesystem::path& output_file_path, std::unique_ptr<layouter> layouter);

        [[nodiscard]] auto& get_pdf_writer() noexcept { return pdf_writer_; }
        [[nodiscard]] auto& get_catalog() const noexcept { return catalog_; }
        [[nodiscard]] auto get_catalog_size() const noexcept { return catalog_.movies.size(); }

    private:
        PDFWriter pdf_writer_{};
        catalog catalog_{};
    };
}  // namespace tmcppc::movies::pdf
