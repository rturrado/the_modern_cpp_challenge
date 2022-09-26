#pragma once

#include "../png/png_writer_wrapper.h"
#include "barcode.h"
#include "env.h"

#include <algorithm>  // for_each
#include <filesystem>
#include <memory>  // make_unique, unique_ptr
#include <string_view>


namespace tmcppc::ean_13::barcode_png {
    using namespace tmcppc::png;


    namespace layout {
        static inline const int bounding_box_height{ 150 };

        struct margin {
            static inline const int top{ 5 };
            static inline const int bottom{ 5 };
            static inline const int left{ 5 };
            static inline const int right{ 5 };
        };
        struct bar {
            static inline const int width{ 2 };
        };
        struct left_quiet_zone {
            static inline const point_2d start_position{ margin::left, margin::bottom };
            static inline const int width{ 20 };
            static inline const int height{ bounding_box_height };
        };
        struct digit {
            static inline const int width{ 5 * bar::width };
            static inline const int height{ 15 };
            static inline const int x_offset{ bar::width };
        };
        struct digit_group {
            static inline const int element_width{ 2 * digit::x_offset + digit::width };
            static inline const int width{ 6 * element_width };
            static inline const int height{ digit::height };
        };
        struct first_digit : public digit_group {
            static inline const point_2d start_position{ margin::left, margin::bottom };
            static inline const int width{ digit::width };
        };
        struct marker {
            static inline const int height{ 145 };
            static inline const int y_offset{ bounding_box_height - height };
        };
        struct start_marker : public marker {
            static inline const point_2d start_position{
                left_quiet_zone::start_position.x + left_quiet_zone::width,
                margin::bottom + marker::y_offset
            };
            static inline const int width{ 3 * bar::width };
        };
        struct digit_bar {
            static inline const int width{ 7 * bar::width };
            static inline const int height{ 135 };
            static inline const int y_offset{ bounding_box_height - height };
        };
        struct digit_bar_group {
            static inline const int width{ 6 * digit_bar::width };
        };
        struct first_digit_bar_group : public digit_bar_group {
            static inline const point_2d start_position{
                start_marker::start_position.x + start_marker::width,
                margin::bottom + digit_bar::y_offset
            };
        };
        struct first_digit_group : public digit_group {
            // First bar group starts with blank, and digits below look better with a 1-bar-width offset
            static inline const point_2d start_position{
                first_digit_bar_group::start_position.x + bar::width,
                margin::bottom
            };
        };
        struct center_marker {
            static inline const point_2d start_position{
                first_digit_bar_group::start_position.x + first_digit_bar_group::width,
                margin::bottom + marker::y_offset
            };
            static inline const int width{ 5 * layout::bar::width };
        };
        struct second_digit_bar_group : public digit_bar_group {
            static inline const point_2d start_position{
                center_marker::start_position.x + center_marker::width,
                margin::bottom + digit_bar::y_offset
            };
        };
        struct second_digit_group : public digit_group {
            static inline const point_2d start_position{
                second_digit_bar_group::start_position.x,
                margin::bottom
            };
        };
        struct end_marker {
            static inline const point_2d start_position{
                second_digit_bar_group::start_position.x + second_digit_bar_group::width,
                margin::bottom + marker::y_offset
            };
            static inline const int width{ 3 * layout::bar::width };
        };
        struct right_quite_zone {
            static inline const point_2d start_position{
                end_marker::start_position.x + end_marker::width,
                margin::bottom
            };
            static inline const int width{ 15 };
            static inline const int height{ bounding_box_height };
        };
        struct lmi {
            static inline const point_2d start_position{
                end_marker::start_position.x + end_marker::width,
                margin::bottom
            };
            static inline const int width{ 7 * bar::width };
            static inline const int height{ 12 };
            static inline const int x_offset{ bar::width };
        };
        struct bounding_box {
            static inline const point_2d start_position{ margin::left, margin::bottom };
            static inline const int width{ right_quite_zone::start_position.x + right_quite_zone::width - margin::left };
            static inline const int height{ bounding_box_height };
        };
        struct image {
            [[maybe_unused]] static inline const point_2d start_position{ 1, 1 };
            static inline const int width{ bounding_box::start_position.x + bounding_box::width + margin::right };
            static inline const int height{ bounding_box::start_position.y + bounding_box::height + margin::top };
        };
    }  // namespace layout


    namespace controls {
        struct base {
            virtual void paint(png_writer& png_writer) const = 0;
            [[nodiscard]] virtual point_2d get_start_position() const = 0;
            virtual ~base() = default;
        };

        // Bar groups
        //
        struct bar_group : public base {
            static void paint_bar(png_writer& png_writer, const point_2d start_position, int width, int height) {
                png_writer.plot_filled_rectangle(
                    rectangle_2d{
                        .bottom_left = { start_position.x, start_position.y },
                        .top_right = { start_position.x + width - 1, start_position.y + height - 1 }
                    },
                    rgb{}
                );
            }

            template <size_t N>
            point_2d paint_bar_group(
                png_writer& png_writer,
                const std::bitset<N>& bs,
                point_2d start_position,
                int width, int height) const {

                for (auto i{ std::ssize(bs) - 1 }; i >= 0; i--) {
                    if (bs[i]) {
                        paint_bar(png_writer, start_position, width, height);
                    }
                    start_position.x += width;
                }
                return start_position;
            }
        };
        struct start_marker : public bar_group {
            void paint(png_writer& writer) const override {
                paint_bar_group(writer, barcode::start_marker, get_start_position(), layout::bar::width, layout::marker::height);
            }
            [[nodiscard]] point_2d get_start_position() const override { return layout::start_marker::start_position; };
        };
        struct center_marker : public bar_group {
            void paint(png_writer& writer) const override {
                paint_bar_group(writer, barcode::center_marker, get_start_position(), layout::bar::width, layout::marker::height);
            }
            [[nodiscard]] point_2d get_start_position() const override { return layout::center_marker::start_position; };
        };
        struct end_marker : public bar_group {
            void paint(png_writer& writer) const override {
                paint_bar_group(writer, barcode::end_marker, get_start_position(), layout::bar::width, layout::marker::height);
            }
            [[nodiscard]] point_2d get_start_position() const override { return layout::end_marker::start_position; };
        };
        struct digit_bar_group : public bar_group {
            explicit digit_bar_group(const digit_group_bs& bs)
                : bs_{ bs }
            {}
            void paint(png_writer& writer) const override {
                auto start_position{ get_start_position() };
                for (const auto& digit_bs : bs_) {
                    paint_bar_group(writer, digit_bs, start_position, layout::bar::width, layout::digit_bar::height);
                    start_position.x += layout::digit_group::element_width;
                }
            }
        private:
            digit_group_bs bs_{};
        };
        struct first_digit_bar_group : public digit_bar_group {
            explicit first_digit_bar_group(const digit_group_bs& bs)
                : digit_bar_group{ bs }
            {}
            [[nodiscard]] point_2d get_start_position() const override { return layout::first_digit_bar_group::start_position; };
        };
        struct second_digit_bar_group : public digit_bar_group {
            explicit second_digit_bar_group(const digit_group_bs& bs)
                : digit_bar_group{ bs }
            {}
            [[nodiscard]] point_2d get_start_position() const override { return layout::second_digit_bar_group::start_position; };
        };

        // Digit groups
        //
        struct digit_group : public base {
            explicit digit_group(std::string_view digit_group)
                : digit_group_{ digit_group }
            {}
            void paint(png_writer& writer) const override {
                const auto font_file_path{ env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
                auto start_position{ get_start_position() };
                for (auto&& digit : digit_group_) {
                    writer.plot_text(
                        font_file_path.string(),
                        layout::digit::height,
                        start_position,
                        0.0,  // angle
                        std::string{ digit },
                        rgb{}
                    );
                    start_position.x += layout::digit_group::element_width;
                }
            }
        private:
            std::string_view digit_group_{};
        };
        struct first_digit : public digit_group {
            explicit first_digit(std::string_view digit)
                : digit_group{ digit }
            {}
            [[nodiscard]] point_2d get_start_position() const override { return layout::first_digit::start_position; };
        };
        struct first_digit_group : public digit_group {
            explicit first_digit_group(std::string_view dg)
                : digit_group{ dg }
            {}
            [[nodiscard]] point_2d get_start_position() const override { return layout::first_digit_group::start_position; };
        };
        struct second_digit_group : public digit_group {
            explicit second_digit_group(std::string_view dg)
                : digit_group{ dg }
            {}
            [[nodiscard]] point_2d get_start_position() const override { return layout::second_digit_group::start_position; };
        };

        // LMI
        //
        struct lmi : public base {
            void paint(png_writer& writer) const override {
                // It should be an angle, two lines, but I find a triangle more beautiful
                writer.plot_filled_triangle(
                    { layout::lmi::start_position.x + layout::lmi::x_offset, layout::lmi::start_position.y + layout::lmi::height },
                    { layout::lmi::start_position.x + layout::lmi::width, layout::lmi::start_position.y + layout::lmi::height / 2 },
                    { layout::lmi::start_position.x + layout::lmi::x_offset, layout::lmi::start_position.y },
                    rgb{}
                );
            }
            [[nodiscard]] point_2d get_start_position() const override { return layout::lmi::start_position; };
        };
    }  // namespace controls


    struct generator {
        void operator()(const barcode& code, double background_colour, const std::filesystem::path& image_path) {
            auto writer = png_writer{ layout::image::width, layout::image::height, background_colour, image_path.string() };

            std::vector<std::unique_ptr<controls::base>> vcontrols;

            vcontrols.push_back(std::make_unique<controls::start_marker>());
            vcontrols.push_back(std::make_unique<controls::center_marker>());
            vcontrols.push_back(std::make_unique<controls::end_marker>());
            vcontrols.push_back(std::make_unique<controls::first_digit_bar_group>(code.get_first_digit_group_bs()));
            vcontrols.push_back(std::make_unique<controls::second_digit_bar_group>(code.get_second_digit_group_bs()));
            vcontrols.push_back(std::make_unique<controls::first_digit>(code.get_first_digit_string()));
            vcontrols.push_back(std::make_unique<controls::first_digit_group>(code.get_first_digit_group_string()));
            vcontrols.push_back(std::make_unique<controls::second_digit_group>(code.get_second_digit_group_string()));
            vcontrols.push_back(std::make_unique<controls::lmi>());

            std::ranges::for_each(vcontrols, [&writer](auto& control_up) { control_up->paint(writer); });
        }
    };
}  // namespace tmcppc::ean_13::barcode_png
