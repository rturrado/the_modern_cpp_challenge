#pragma once

#include <filesystem>
#include <PDFWriter/AbstractContentContext.h>
#include <PDFWriter/PageContentContext.h>
#include <PDFWriter/PDFPage.h>
#include <PDFWriter/PDFRectangle.h>
#include <PDFWriter/PDFWriter.h>
#include <stdexcept>  // runtime_error
#include <string>


namespace tmcppc::pdf_writer {
    using TextOptions = AbstractContentContext::TextOptions;
    using ImageOptions = AbstractContentContext::ImageOptions;

    // Runtime errors
    struct start_pdf_error : public std::runtime_error {
        explicit start_pdf_error(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "trying to start PDF: " };
    };
    struct end_pdf_error : public std::runtime_error {
        explicit end_pdf_error(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "trying to end PDF: " };
    };
    struct end_page_content_context_error : public std::runtime_error {
        explicit end_page_content_context_error(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "trying to end page content context: " };
    };
    struct write_page_and_release_error : public std::runtime_error {
        explicit write_page_and_release_error(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "trying to write page and release: " };
    };
    struct get_font_for_file_error : public std::runtime_error {
        explicit get_font_for_file_error(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "trying to get font for file: " };
    };
    struct get_image_dimensions_error : public std::runtime_error {
        explicit get_image_dimensions_error(const std::string& path) : std::runtime_error{ message_ + path } {}
    private:
        static inline std::string message_{ "trying to get image dimensions for file: " };
    };


    // PDF writer function wrappers
    inline auto start_pdf(PDFWriter& pdf_writer, const std::filesystem::path& output_file_path) {
        auto output_file_path_str{ output_file_path.generic_string() };
        if (pdf_writer.StartPDF(output_file_path_str, ePDFVersion17) != eSuccess) {
            throw tmcppc::pdf_writer::start_pdf_error{ output_file_path_str };
        }
    }
    inline auto end_pdf(PDFWriter& pdf_writer) {
        if (pdf_writer.EndPDF() != eSuccess) {
            throw tmcppc::pdf_writer::end_pdf_error{ pdf_writer.GetOutputFile().GetFilePath() };
        }
    }
    inline auto create_page(double width, double height) {
        auto page{ new PDFPage{} };
        page->SetMediaBox(PDFRectangle{ 0, 0, width, height });
        return page;
    }
    inline auto write_page_and_release(PDFWriter& pdf_writer, PDFPage* page) {
        if (pdf_writer.WritePageAndRelease(page) != eSuccess) {
            throw tmcppc::pdf_writer::write_page_and_release_error{ pdf_writer.GetOutputFile().GetFilePath() };
        }
    }
    inline auto start_page_content_context(PDFWriter& pdf_writer, PDFPage* page) {
        return pdf_writer.StartPageContentContext(page);
    }
    inline auto end_page_content_context(PDFWriter& pdf_writer, PageContentContext* ctx) {
        if (pdf_writer.EndPageContentContext(ctx) != eSuccess) {
            throw tmcppc::pdf_writer::end_page_content_context_error{ pdf_writer.GetOutputFile().GetFilePath() };
        }
    }
    inline auto get_font_for_file(PDFWriter& pdf_writer, const std::filesystem::path& font_file_path) {
        if (not std::filesystem::exists(font_file_path)) {
            throw tmcppc::pdf_writer::get_font_for_file_error{ font_file_path.generic_string() };
        }
        return pdf_writer.GetFontForFile(font_file_path.string());
    }
    inline auto write_text(PageContentContext* ctx, double x, double y, const std::string& text, const TextOptions& text_options) {
        ctx->WriteText(x, y, text, text_options);
    }
    inline auto draw_line(PageContentContext* ctx, double x1, double y1, double x2, double y2) {
        ctx->DrawPath({ {x1, y1}, {x2, y2} });
    }
    inline auto get_image_dimensions(PDFWriter& pdf_writer, const std::filesystem::path& image_file_path) {
        if (not std::filesystem::exists(image_file_path)) {
            throw tmcppc::pdf_writer::get_image_dimensions_error{ image_file_path.generic_string() };
        }
        return pdf_writer.GetImageDimensions(image_file_path.string());
    }
    inline auto draw_image(PageContentContext* ctx, double x, double y, const std::filesystem::path& image_file_path,
        const ImageOptions& image_options = ImageOptions{}) {

        ctx->DrawImage(x, y, image_file_path.string(), image_options);
    }


    // Helper functions
    inline void start_page_and_page_content_context(PDFWriter& pdf_writer, PDFPage** ppage, PageContentContext** pctx,
        double page_width, double page_height) {

        if (ppage and not *ppage) {
            *ppage = create_page(page_width, page_height);
        }
        if (*ppage and pctx and not *pctx) {
            *pctx = start_page_content_context(pdf_writer, *ppage);
        };
    };
    inline void end_page_and_page_content_context(PDFWriter& pdf_writer, PDFPage** ppage, PageContentContext** pctx) {
        if (pctx and *pctx) {
            end_page_content_context(pdf_writer, *pctx);
            *pctx = nullptr;
        }
        if (ppage and *ppage) {
            tmcppc::pdf_writer::write_page_and_release(pdf_writer, *ppage);
            *ppage = nullptr;
        }
    };
}  // tmcppc::pdf_writer
