#pragma once

#include "env.h"
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
#include <fmt/ostream.h>
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
    // Page layout
    const size_t movies_per_page{ 25 };

    // doc
    struct doc {
    private:
        PDFWriter pdf_writer{};
        AbstractContentContext::TextOptions text_options{ nullptr, font_height, AbstractContentContext::eGray, 0 };

        void draw_line_separator(PageContentContext* ctx, double current_y) {
            using namespace tmcppc::pdf_writer;

            double start_x{ margin_left };
            double end_x{ page_width - margin_right };
            draw_line(ctx, start_x, current_y, end_x, current_y);
        };

    public:
        catalog catalog_{};

        doc(const catalog& c) : catalog_{ c } {
            auto font_path{ env::get_instance().get_resource_folder_path() / "fonts" / "pala.ttf" };
            auto font{ pdf_writer.GetFontForFile(font_path.string()) };
            text_options.font = font;
        }

        void save_as_table(const std::filesystem::path& output_file_path) {
            using namespace tmcppc::pdf_writer;

            start_pdf(pdf_writer, output_file_path);

            // Movies
            for (int i{ 0 }; i < catalog_.movies.size(); ) {
                PDFPage* page{};
                PageContentContext* ctx{};
                start_page_and_page_content_context(pdf_writer, &page, &ctx, page_width, page_height);

                // Cursor
                double current_y{ page_height - margin_top };
                double start_x{};

                // Title (only in the first page)
                if (i == 0) {
                    current_y -= font_height;
                    start_x = margin_left + font_width;
                    write_text(ctx, start_x, current_y, "List of movies", text_options);
                }

                // Line separator
                current_y -= line_spacing;
                draw_line_separator(ctx, current_y);

                // Movies per page
                auto page_movies_end{ std::min(catalog_.movies.size() - i, movies_per_page) };
                for (int j{ 0 }; j < page_movies_end; ++j, ++i) {
                    auto& movie{ catalog_.movies[i] };
                    auto movie_year_str{ fmt::format("({})", static_cast<int>(movie.year)) };
                    auto movie_length_str{ fmt::format("{}: {:02}", movie.length / 60, movie.length % 60) };
                    auto movie_title_and_year_str{ fmt::format("{} {}", movie.title, movie_year_str) };

                    // Movie
                    current_y -= (font_height + line_spacing);
                    start_x = margin_left + font_width;
                    write_text(ctx, start_x, current_y, movie_title_and_year_str, text_options);  // title, year
                    start_x = page_width - margin_right - font_width * movie_length_str.size();
                    write_text(ctx, start_x, current_y, movie_length_str, text_options);  // length
                }

                // Line separator
                current_y -= line_spacing;
                draw_line_separator(ctx, current_y);

                end_page_and_page_content_context(pdf_writer, &page, &ctx);
            }

            end_pdf(pdf_writer);
        }
    };
}  // namespace tmcppc::movies::pdf
