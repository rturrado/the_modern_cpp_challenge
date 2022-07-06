#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/pdf_movies.h"
#include "chapter_09_data_serialization/pdf_writer_wrapper.h"

#include "env.h"

#include "PDFWriter/AbstractContentContext.h"
#include "PDFWriter/PageContentContext.h"
#include "PDFWriter/PDFPage.h"
#include "PDFWriter/PDFRectangle.h"
#include "PDFWriter/PDFWriter.h"

#include <cmath>
#include <filesystem>
#include <fmt/format.h>
#include <fmt/ostream.h>


namespace tmcppc::movies::pdf {
    // Layouter
    void layouter::set_font(PDFWriter& pdf_writer) {
        if (text_options.font == nullptr) {
            const auto font_path{ env::get_instance().get_resource_folder_path() / "fonts" / "pala.ttf" };
            text_options.font = tmcppc::pdf_writer::get_font_for_file(pdf_writer, font_path);
        }
    }


    // List layouter
    /* explicit */ list_layouter::list_layouter(int movies_per_page)
        : movies_per_page_{ movies_per_page }
        , page_counter_{ 0 }
        , is_first_movie_of_page_{ true } {
        reset_cursor();
    }

    void list_layouter::print(doc* doc, const movie& movie) {
        static PDFPage* page{};
        static PageContentContext* ctx{};

        auto& pdf_writer{ doc->get_pdf_writer() };

        if (is_first_movie_of_page()) {
            set_font(doc->get_pdf_writer());
            tmcppc::pdf_writer::start_page_and_page_content_context(pdf_writer, &page, &ctx, page_width, page_height);
            print_title(ctx);
            print_line_separator(ctx);
            set_is_first_movie_of_page(false);
        }

        print_movie(ctx, movie);

        if (is_last_movie_of_page(doc)) {
            print_line_separator(ctx);
            tmcppc::pdf_writer::end_page_and_page_content_context(pdf_writer, &page, &ctx);
            reset_cursor();
            set_is_first_movie_of_page(true);
        }
    }

    [[nodiscard]] bool list_layouter::is_first_movie_of_page() const noexcept {
        return is_first_movie_of_page_;
    }

    [[nodiscard]] bool list_layouter::is_last_movie_of_page(doc* doc) const noexcept {
        return
            page_counter_ == doc->get_catalog_size() or
            page_counter_ % movies_per_page_ == 0 or
            current_y - (font_height + line_spacing) < margin_bottom;
    }

    void list_layouter::set_is_first_movie_of_page(bool flag) noexcept {
        is_first_movie_of_page_ = flag;
    }

    void list_layouter::reset_cursor() noexcept{
        current_y = page_height - margin_top;
    }

    void list_layouter::print_title(PageContentContext* ctx) {
        current_y -= font_height;
        double start_x{ margin_left + font_width };
        tmcppc::pdf_writer::write_text(ctx, start_x, current_y, "List of movies", text_options);
    }

    void list_layouter::print_line_separator(PageContentContext* ctx) {
        current_y -= line_spacing;
        double start_x{ margin_left };
        double end_x{ page_width - margin_right };
        tmcppc::pdf_writer::draw_line(ctx, start_x, current_y, end_x, current_y);
    }

    void list_layouter::print_movie(PageContentContext* ctx, const movie& movie) {
        auto movie_year_str{ fmt::format("({})", static_cast<int>(movie.year)) };
        auto movie_length_str{ fmt::format("{}: {:02}", movie.length / 60, movie.length % 60) };
        auto movie_title_and_year_str{ fmt::format("{} {}", movie.title, movie_year_str) };

        current_y -= (font_height + line_spacing);
        double start_x{ margin_left + font_width };
        tmcppc::pdf_writer::write_text(ctx, start_x, current_y, movie_title_and_year_str, text_options);  // title, year
        start_x = page_width - margin_right - font_width * movie_length_str.size();
        tmcppc::pdf_writer::write_text(ctx, start_x, current_y, movie_length_str, text_options);  // length

        page_counter_++;
    }


    // PDF document
    void doc::save_to(const std::filesystem::path& output_file_path, std::unique_ptr<layouter> layouter) {
        tmcppc::pdf_writer::start_pdf(pdf_writer_, output_file_path);
        for (auto&& movie : catalog_.movies) {
            layouter->print(this, movie);
        }
        tmcppc::pdf_writer::end_pdf(pdf_writer_);
    }
}  // namespace tmcppc::movies::pdf
