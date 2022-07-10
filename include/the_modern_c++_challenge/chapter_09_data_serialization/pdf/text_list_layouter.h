#pragma once

#include "doc.h"
#include "layouter.h"

#include "PDFWriter/AbstractContentContext.h"

#include <stdexcept>  // runtime_error
#include <string>


namespace tmcppc::pdf {
    class text_list_layouter : public layouter {
        using TextOptions = AbstractContentContext::TextOptions;

    public:
        text_list_layouter() = default;
        text_list_layouter(const text_list_layouter& other) = delete;
        text_list_layouter(text_list_layouter&& other) noexcept = delete;
        text_list_layouter& operator=(const text_list_layouter& other) = delete;
        text_list_layouter& operator=(text_list_layouter&& other) noexcept = delete;
        ~text_list_layouter() = default;

        explicit text_list_layouter(int text_lines_per_page)
            : text_lines_per_page_{ text_lines_per_page }
            , text_line_counter_{ 0 } {
        
            if (text_lines_per_page_ == 0) {
                throw std::runtime_error("trying to create a text_list_layouter with a zero text_lines_per_page");
            }
        }

        [[nodiscard]] virtual image_control position_image(doc*, double, double) {
            return {};
        };

        [[nodiscard]] virtual line_control position_line_separator() override {
            set_cursor(current_y_ - line_spacing_);
            double start_x{ margin_left_ };
            double end_x{ page_width_ - margin_right_ };
            return { start_x, current_y_, end_x, current_y_ };
        }

        [[nodiscard]] virtual text_control position_text(doc* doc, const std::string& text, bool add_new_line,
            const text_alignment& alignment) override {

            if (add_new_line) {
                text_line_counter_++;
                if (not text_fits_in_current_page()) {
                    doc->end_page();
                    reset_cursor();
                    doc->start_page(page_width_, page_height_);
                }
                set_cursor(current_y_ - text_font_height_ - line_spacing_);
            }
            double x{ get_text_x(text, text_font_width_, alignment) };
            return text_control{ x, current_y_, get_text_options(doc) };
        }

        [[nodiscard]] virtual text_control position_title(doc* doc, const std::string& text,
            const text_alignment& alignment) override {

            set_cursor(current_y_ - title_font_height_);
            double x{ get_text_x(text, title_font_width_, alignment) };
            return text_control{ x, current_y_, get_title_options(doc) };
        }

    private:
        // Text font
        double text_font_width_{ 8 };
        double text_font_height_{ 14 };
        // Title font
        double title_font_width_{ 9 };
        double title_font_height_{ 16 };
        // Line spacing
        double line_spacing_{ 5 };
        // Text lines
        int text_lines_per_page_{ 40 };
        int text_line_counter_{ 0 };
        // Text options
        TextOptions text_options_{ nullptr };
        TextOptions title_options_{ nullptr };

        [[nodiscard]] bool text_fits_in_current_page() const {
            return
                ((text_line_counter_ == 1) or (text_line_counter_ % text_lines_per_page_ != 1)) and
                ((current_y_ - text_font_height_ - 2 * line_spacing_) > margin_bottom_);
        }

        [[nodiscard]] double get_text_x(const std::string& text, double font_width, const text_alignment& alignment) {
            switch (alignment) {
                case text_alignment::right: return page_width_ - margin_right_ - font_width * text.size();
                case text_alignment::left:
                default: return margin_left_ + font_width;
            }
        }

        [[nodiscard]] TextOptions get_text_options(doc* doc) {
            if (text_options_.font == nullptr) {
                text_options_.font = doc->get_font();
                text_options_.fontSize = text_font_height_;
                text_options_.colorSpace = AbstractContentContext::eGray;
                text_options_.colorValue = 0;
            }
            return text_options_;
        }
        [[nodiscard]] TextOptions get_title_options(doc* doc) {
            if (title_options_.font == nullptr) {
                title_options_ = get_text_options(doc);
                title_options_.fontSize = title_font_height_;
            }
            return title_options_;
        }
    };
}  // namespace tmcppc::pdf
