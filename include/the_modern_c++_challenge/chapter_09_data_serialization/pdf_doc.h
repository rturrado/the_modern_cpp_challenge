#pragma once

#include "env.h"
#include "pdf_layouter.h"
#include "pdf_writer_wrapper.h"

#include "PDFWriter/PDFWriter.h"

#include <filesystem>
#include <memory>  // unique_ptr
#include <string>

class PDFPage;
class PageContentContext;
class PDFUsedFont;


namespace tmcppc::pdf {
    class pdf_doc {
    public:
        virtual void save_to(const std::filesystem::path& output_file_path, std::unique_ptr<layouter> layouter) = 0;

        virtual void start_page(double page_width, double page_height) = 0;
        virtual void end_page() = 0;

        [[nodiscard]] auto& get_pdf_writer() noexcept { return pdf_writer_; }

        void set_font() {
            if (font_ == nullptr) {
                const auto font_path{ env::get_instance().get_resource_folder_path() / "fonts" / "pala.ttf" };
                font_ = tmcppc::pdf_writer::get_font_for_file(pdf_writer_, font_path);
            }
        }

        [[nodiscard]] PDFUsedFont* get_font() {
            if (font_ == nullptr) {
                set_font();
            }
            return font_;
        }

    protected:
        PDFWriter pdf_writer_{};
        PDFPage* current_page_{ nullptr };
        PageContentContext* current_ctx_{ nullptr };
        PDFUsedFont* font_{ nullptr };
        std::unique_ptr<layouter> layouter_{};
        int page_counter_{ 0 };

        virtual void start_pdf(const std::filesystem::path& output_file_path) = 0;
        virtual void end_pdf() = 0;

        [[nodiscard]] bool is_first_page() const { return page_counter_ == 0; }
    };
}  // namespace tmcppc::pdf
