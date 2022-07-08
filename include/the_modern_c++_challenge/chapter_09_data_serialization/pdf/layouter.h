#pragma once

#include "PDFWriter/AbstractContentContext.h"

#include <string>


namespace tmcppc::pdf {
    class doc;

    // Text alignment
    enum class text_alignment { left, right };

    // Image control
    struct image_control {
        double x{};
        double y{};
        AbstractContentContext::ImageOptions image_options{};
    };

    // Line control
    struct line_control {
        double start_x{};
        double start_y{};
        double end_x{};
        double end_y{};
    };

    // Text control
    struct text_control {
        double start_x{};
        double start_y{};
        AbstractContentContext::TextOptions text_options{ nullptr };
    };

    // Layouter
    class layouter {
    public:
        layouter() {
            reset_cursor();
        }
        layouter(const layouter& other) = delete;
        layouter(layouter&& other) noexcept = delete;
        layouter& operator=(const layouter& other) = delete;
        layouter& operator=(layouter&& other) noexcept = delete;
        virtual ~layouter() = default;

        [[nodiscard]] virtual image_control position_image(
            doc* doc, double image_width, double image_height) = 0;
        [[nodiscard]] virtual line_control position_line_separator() = 0;
        [[nodiscard]] virtual text_control position_text(
            doc* doc, const std::string& text, bool add_new_line, const text_alignment& alignment) = 0;
        [[nodiscard]] virtual text_control position_title(
            doc* doc, const std::string& text, const text_alignment& alignment) = 0;

        [[nodiscard]] auto get_page_width() const { return page_width_; }
        [[nodiscard]] auto get_page_height() const { return page_height_; }

    protected:
        // Margins
        double margin_left_{ 20 };
        double margin_right_{ 20 };
        double margin_top_{ 30 };
        double margin_bottom_{ 30 };
        // Page
        double page_width_{ 595 };
        double page_height_{ 842 };
        const double page_width_available_{ page_width_ - margin_left_ - margin_right_ };
        const double page_height_available_{ page_height_ - margin_top_ - margin_bottom_ };
        // Text
        double font_width_{ 8 };
        double font_height_{ 14 };
        double line_spacing_{ 5 };
        // Image
        double image_spacing_{ 10 };
        // Cursor
        double current_y_{ 0 };

        // Page heights (double) equality and comparison
        bool equals(double a, double b) { return (a - b < 0.1) and (b - a < 0.1); };
        bool less_than(double a, double b) { return (b - a > 0.1); };

        void reset_cursor() noexcept { current_y_ = page_height_ - margin_top_; }
        void set_cursor(double y) noexcept { current_y_ = y; }
    };
}  // namespace tmcppc::pdf
