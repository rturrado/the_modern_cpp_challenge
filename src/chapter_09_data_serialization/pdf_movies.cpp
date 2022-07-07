#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/pdf_doc.h"
#include "chapter_09_data_serialization/pdf_layouter.h"
#include "chapter_09_data_serialization/pdf_movies.h"
#include "chapter_09_data_serialization/pdf_writer_wrapper.h"
#include "env.h"

#include "PDFWriter/AbstractContentContext.h"
#include "PDFWriter/PageContentContext.h"
#include "PDFWriter/PDFPage.h"
#include "PDFWriter/PDFRectangle.h"
#include "PDFWriter/PDFWriter.h"

#include <filesystem>
#include <fmt/format.h>
#include <string>


namespace tmcppc::pdf {
    using TextOptions = tmcppc::pdf_writer::TextOptions;


    // Text list layouter
    text_list_layouter::text_list_layouter(int text_lines_per_page)
        : text_lines_per_page_{ text_lines_per_page }
        , text_line_counter_{ 0 }
        {}

    [[nodiscard]] bool text_list_layouter::text_fits_in_current_page() const {
        return
            ((text_line_counter_ % text_lines_per_page_) != 0) and
            ((current_y_ - font_height_ - 2 * line_spacing_) > margin_bottom_);
    }

    [[nodiscard]] line_control text_list_layouter::position_line() {
        reset_cursor(current_y_ - line_spacing_);
        double start_x{ margin_left_ };
        double end_x{ page_width_ - margin_right_ };
        return { start_x, current_y_, end_x, current_y_ };
    }

    [[nodiscard]] text_control text_list_layouter::position_text(pdf_doc* doc, const std::string& text, bool add_new_line,
        const text_alignment& alignment) {

        if (add_new_line) {
            if (not text_fits_in_current_page()) {
                doc->end_page();
                reset_cursor();
                doc->start_page(page_width_, page_height_);
            }
            text_line_counter_++;
            reset_cursor(current_y_ - font_height_ - line_spacing_);
        }
        double x{ get_text_x(text, font_width_, alignment) };
        return text_control{ x, current_y_, get_text_options(doc) };
    }

    [[nodiscard]] text_control text_list_layouter::position_title(pdf_doc* doc, const std::string& text,
        const text_alignment& alignment) {

        reset_cursor(current_y_ - title_font_height_ - line_spacing_);
        double x{ get_text_x(text, title_font_width_, alignment) };
        return text_control{ x, current_y_, get_title_text_options(doc) };
    }

    [[nodiscard]] TextOptions text_list_layouter::get_text_options(pdf_doc* doc) {
        if (text_options_.font == nullptr) {
            text_options_.font = doc->get_font();
            text_options_.fontSize = font_height_;
            text_options_.colorSpace = AbstractContentContext::eGray;
            text_options_.colorValue = 0;
        }
        return text_options_;
    }

    [[nodiscard]] TextOptions text_list_layouter::get_title_text_options(pdf_doc* doc) {
        if (title_text_options_.font == nullptr) {
            title_text_options_ = get_text_options(doc);
            title_text_options_.fontSize = title_font_height_;
        }
        return title_text_options_;
    }

    [[nodiscard]] double text_list_layouter::get_text_x(const std::string& text, double font_width, const text_alignment& alignment) {
        switch (alignment) {
            case text_alignment::right: return page_width_ - margin_right_ - font_width * text.size();
            case text_alignment::left:
            default: return margin_left_ + font_width;
        }
    }


    // Movies document
    void movies_doc::save_to(const std::filesystem::path& output_file_path, std::unique_ptr<layouter> layouter) {
        layouter_ = std::move(layouter);
        start_pdf(output_file_path);
        for (auto&& movie : catalog_.movies) {
            auto movie_year_str{ fmt::format("({})", static_cast<int>(movie.year)) };
            auto movie_title_and_year_str{ fmt::format("{} {}", movie.title, movie_year_str) };
            auto movie_length_str{ fmt::format("{}: {:02}", movie.length / 60, movie.length % 60) };

            print_text_line(movie_title_and_year_str, true, text_alignment::left);
            print_text_line(movie_length_str, false, text_alignment::right);
        }
        end_pdf();
    }

    void movies_doc::start_pdf(const std::filesystem::path& output_file_path) {
        tmcppc::pdf_writer::start_pdf(pdf_writer_, output_file_path);
        set_font();
    }

    void movies_doc::end_pdf() {
        end_page();
        tmcppc::pdf_writer::end_pdf(pdf_writer_);
    }

    void movies_doc::start_page(double page_width, double page_height) {
        tmcppc::pdf_writer::start_page_and_page_content_context(pdf_writer_, &current_page_, &current_ctx_, page_width, page_height);
        if (is_first_page()) {
            print_title();
        }
        print_line_separator();
        page_counter_++;
    }

    void movies_doc::end_page() {
        if (current_page_ and current_ctx_) {
            print_line_separator();
            tmcppc::pdf_writer::end_page_and_page_content_context(pdf_writer_, &current_page_, &current_ctx_);
        }
    }

    void movies_doc::print_title() {
        auto text{ "List of movies" };
        auto [start_x, start_y, text_options] = layouter_->position_title(this, text, text_alignment::left);
        tmcppc::pdf_writer::write_text(current_ctx_, start_x, start_y, text, text_options);
    }

    void movies_doc::print_text_line(const std::string& text, bool add_new_line, const text_alignment& align) {
        auto [start_x, start_y, text_options] = layouter_->position_text(this, text, add_new_line, align);
        tmcppc::pdf_writer::write_text(current_ctx_, start_x, start_y, text, text_options);
    }

    void movies_doc::print_line_separator() {
        auto [start_x, start_y, end_x, end_y] = layouter_->position_line();
        tmcppc::pdf_writer::draw_line(current_ctx_, start_x, start_y, end_x, end_y);
    }
}  // namespace tmcppc::movies::pdf
