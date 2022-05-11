#pragma once

#include "movies.h"
#include "pdf_writer_wrapper.h"

#include "PDFWriter/AbstractContentContext.h"
#include "PDFWriter/PageContentContext.h"
#include "PDFWriter/PDFPage.h"
#include "PDFWriter/PDFRectangle.h"
#include "PDFWriter/PDFWriter.h"

#include <cmath>
#include <filesystem>
#include <fmt/format.h>
#include <iomanip>  // setfill, setw
#include <sstream>  // ostringstream
#include <string>


namespace tmcppc::movies::pdf {
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
    // Text
    const double font_width{ 8 };
    const double font_height{ 14 };
    const double line_spacing{ 5 };
    // Font
    const auto font_path{ std::filesystem::current_path() / "res" / "fonts" / "pala.ttf" };

    // doc
    struct doc {
        catalog catalog_{};

        doc() = default;
        doc(const catalog& c) : catalog_{ c } {}

        inline void save_as_table(const std::filesystem::path& output_file_path) {
            // PDF writer
            PDFWriter pdf_writer{};
            tmcppc::pdf_writer::start_pdf(pdf_writer, output_file_path);

            // Font, text options
            const auto font{ pdf_writer.GetFontForFile(font_path.string()) };
            const AbstractContentContext::TextOptions text_options{ font, font_height, AbstractContentContext::eGray, 0 };

            // Movies
            for (auto it{ std::cbegin(catalog_.movies) }; it != std::cend(catalog_.movies); ) {
                // Page
                auto page{ tmcppc::pdf_writer::create_page(page_width, page_height) };

                // Context
                auto ctx{ tmcppc::pdf_writer::start_page_content_context(pdf_writer, page) };

                // Cursor height
                double current_y{ page_height - margin_top };

                // Title (only in the first page)
                if (it == std::cbegin(catalog_.movies)) {
                    current_y -= font_height;
                    tmcppc::pdf_writer::write_text(ctx, margin_left + font_width, current_y, "List of movies", text_options);
                }

                // Line separator
                current_y -= line_spacing;
                tmcppc::pdf_writer::draw_line(ctx, margin_left, current_y, page_width - margin_right, current_y);

                // Page layout
                const size_t movies_per_page{ 25 };

                // Movies per page
                auto page_it_end{ it + std::min(static_cast<size_t>(std::distance(it, std::cend(catalog_.movies))), movies_per_page) };
                for (; it != page_it_end; ++it) {
                    auto movie_year_to_string = [](auto year) {
                        return fmt::format("({})", static_cast<int>(year));
                    };
                    auto movie_length_to_string = [](auto length) {
                        return fmt::format("{}: {:02}", length / 60, length % 60);
                    };

                    auto& movie{ *it };
                    std::string movie_year{ movie_year_to_string(movie.year) };
                    std::string movie_length{ movie_length_to_string(movie.length) };

                    std::ostringstream oss{};
                    oss << movie.title << " " << movie_year;
                    
                    // Movie
                    current_y -= (font_height + line_spacing);
                    tmcppc::pdf_writer::write_text(ctx, margin_left + font_width, current_y, oss.str(), text_options);
                    tmcppc::pdf_writer::write_text(ctx, page_width - margin_right - font_width * movie_length.size(), current_y, movie_length, text_options);
                }

                // Line separator
                current_y -= line_spacing;
                tmcppc::pdf_writer::draw_line(ctx, margin_left, current_y, page_width - margin_right, current_y);

                tmcppc::pdf_writer::end_page_content_context(pdf_writer, ctx);
                tmcppc::pdf_writer::write_page_and_release(pdf_writer, page);
            }

            tmcppc::pdf_writer::end_pdf(pdf_writer);
        }
    };
}  // namespace tmcppc::movies::pdf
