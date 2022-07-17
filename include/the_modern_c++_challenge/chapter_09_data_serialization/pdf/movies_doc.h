#pragma once

#include "../movies.h"
#include "doc.h"
#include "env.h"
#include "layouter.h"
#include "pdf_writer_wrapper.h"

#include "PDFWriter/AbstractContentContext.h"
#include "PDFWriter/PageContentContext.h"
#include "PDFWriter/PDFPage.h"
#include "PDFWriter/PDFRectangle.h"
#include "PDFWriter/PDFWriter.h"

#include <filesystem>
#include <fmt/format.h>
#include <memory>  // unique_ptr
#include <string>
#include <utility>  // move


namespace tmcppc::pdf {
    class movies_doc : public doc {
        using catalog = tmcppc::movies::catalog;

    public:
        movies_doc(const catalog& c) : catalog_{ c } {}

        virtual void start_pdf(const std::filesystem::path& output_file_path) override {
            tmcppc::pdf_writer::start_pdf(pdf_writer_, output_file_path);
            set_font();
        }

        virtual void start_page(double page_width, double page_height) override {
            tmcppc::pdf_writer::start_page_and_page_content_context(pdf_writer_, &current_page_, &current_ctx_, page_width, page_height);
            page_counter_++;
            if (is_first_page()) {
                print_title();
            }
            print_line_separator();
        }

        virtual void end_pdf() override {
            end_page();
            tmcppc::pdf_writer::end_pdf(pdf_writer_);
        }

        virtual void end_page() override{
            if (current_page_ and current_ctx_) {
                print_line_separator();
                tmcppc::pdf_writer::end_page_and_page_content_context(pdf_writer_, &current_page_, &current_ctx_);
            }
        }

        virtual void save_to(const std::filesystem::path& output_file_path, std::unique_ptr<layouter> layouter) override {
            layouter_ = std::move(layouter);
            start_pdf(output_file_path);
            start_page(layouter_->get_page_width(), layouter_->get_page_height());
            for (auto&& movie : catalog_.movies) {
                auto movie_year_str{ fmt::format("({})", int(movie.year)) };
                auto movie_title_and_year_str{ fmt::format("{} {}", movie.title, movie_year_str) };
                auto movie_length_str{ fmt::format("{}: {:02}", movie.length / 60, movie.length % 60) };

                print_text_line(movie_title_and_year_str, true, text_alignment::left);
                print_text_line(movie_length_str, false, text_alignment::right);
            }
            end_pdf();
        }

    private:
        catalog catalog_{};

        void print_line_separator() {
            auto [start_x, start_y, end_x, end_y] = layouter_->position_line_separator();
            tmcppc::pdf_writer::draw_line(current_ctx_, start_x, start_y, end_x, end_y);
        }

        void print_text_line(const std::string& text, bool add_new_line, const text_alignment& align) {
            auto [start_x, start_y, text_options] = layouter_->position_text(this, text, add_new_line, align);
            tmcppc::pdf_writer::write_text(current_ctx_, start_x, start_y, text, text_options);
        }

        void print_title() {
            auto text{ "List of movies" };
            auto [start_x, start_y, text_options] = layouter_->position_title(this, text, text_alignment::left);
            tmcppc::pdf_writer::write_text(current_ctx_, start_x, start_y, text, text_options);
        }
    };
}  // namespace tmcppc::pdf
