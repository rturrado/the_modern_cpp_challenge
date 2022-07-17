#pragma once

#include "pngwriter.h"

#include <filesystem>
#include <string>


namespace tmcppc::png {
    namespace fs = std::filesystem;

    const fs::path png_file_extension{ "png" };

    inline auto create_png_file_path(const fs::path& file_root_path, const std::string& file_stem) {
        auto file_path{ file_root_path / file_stem };
        file_path.replace_extension(png_file_extension);
        return file_path;
    };

    struct rgb {
        double r{};
        double g{};
        double b{};
    };

    struct point_2d {
        int x{};
        int y{};
    };

    struct line_2d {
        point_2d from{};
        point_2d to{};
    };

    struct rectangle_2d {
        point_2d bottom_left{};
        point_2d top_right{};

        [[nodiscard]] int get_width() const { return top_right.x - bottom_left.x; }
        [[nodiscard]] int get_height() const { return top_right.y - bottom_left.y; }
    };

    struct gradient {
        rgb start{};
        rgb end{};
    };

    class png_writer {
    public:
        png_writer(int width, int height, double background_colour, const fs::path& file_path)
            : width_{ width }, height_{ height }
            , background_colour_{ background_colour }
            , file_path_{ file_path }
            , writer_{ width, height, background_colour, file_path.string().c_str() }
        {}
        png_writer(const png_writer& other) = delete;
        png_writer(png_writer&& other) noexcept = delete;
        png_writer& operator=(const png_writer& other) = delete;
        png_writer& operator=(png_writer&& other) noexcept = delete;
        ~png_writer() { writer_.close(); }

        [[nodiscard]] int get_width() const { return width_; }
        [[nodiscard]] int get_height() const { return height_; }
        [[nodiscard]] double get_background_colour() const { return background_colour_; }
        [[nodiscard]] fs::path get_file_path() const { return file_path_; }

        void plot_filled_rectangle(const rectangle_2d& rectangle, const rgb& colour) {
            writer_.filledsquare(rectangle.bottom_left.x, rectangle.bottom_left.y, rectangle.top_right.x, rectangle.top_right.y,
                colour.r, colour.g, colour.b);
        }

        void plot_filled_triangle(const point_2d& v1, const point_2d& v2, const point_2d& v3, const rgb& colour) {
            writer_.filledtriangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, colour.r, colour.g, colour.b);
        }

        void plot_filled_rectangle_horizontal_gradient(const rectangle_2d& rectangle, const gradient& gradient) {
            const auto width{ rectangle.top_right.x - rectangle.bottom_left.x };
            const auto y0{ rectangle.bottom_left.y };
            const auto y1{ rectangle.top_right.y };

            for (int x{rectangle.bottom_left.x}; x <= rectangle.top_right.x; ++x) {
                auto factor{ static_cast<double>(x) / width };
                auto red{ (gradient.end.r - gradient.start.r) * factor + gradient.start.r };
                auto green{ (gradient.end.g - gradient.start.g) * factor + gradient.start.g };
                auto blue{ (gradient.end.b - gradient.start.b) * factor + gradient.start.b };
                writer_.line(x, y0, x, y1, red, green, blue);
            }
        }

        void plot_line(const line_2d& line, const rgb& colour) {
            writer_.line(line.from.x, line.from.y, line.to.x, line.to.y, colour.r, colour.g, colour.b);
        }

        void plot_text(
            fs::path font_file_path,
            int font_size,
            const point_2d& bottom_left_position,
            double angle,
            std::string text,
            const rgb& colour) {

            writer_.plot_text(
                const_cast<char*>(font_file_path.string().c_str()),
                font_size,
                bottom_left_position.x, bottom_left_position.y,
                angle,
                const_cast<char*>(text.c_str()),
                colour.r, colour.g, colour.b);
        }
    private:
        int width_{};
        int height_{};
        double background_colour_{};
        fs::path file_path_{};

        pngwriter writer_{};
    };
}  // namespace tmcppc::png
