#ifndef EAN_13_BARCODE_PNG_GENERATOR_H
#define EAN_13_BARCODE_PNG_GENERATOR_H

#include "ean_13_barcode.h"
#include "png_writer_wrapper.h"

#include <algorithm>  // for_each
#include <filesystem>
#include <memory>  // make_unique, unique_ptr


namespace rtc::ean_13::barcode_png
{
    using namespace tmcppc::png_writer;


    namespace layout
    {
        static inline const int bounding_box_height{ 150 };

        struct Margin
        {
            static inline const int top{ 5 };
            static inline const int bottom{ 5 };
            static inline const int left{ 5 };
            static inline const int right{ 5 };
        };
        struct Bar
        {
            static inline const int width{ 2 };
        };
        struct LeftQuietZone
        {
            static inline const Point2D start_position{ Margin::left, Margin::bottom };
            static inline const int width{ 20 };
            static inline const int height{ bounding_box_height };
        };
        struct Digit
        {
            static inline const int width{ 5 * Bar::width };
            static inline const int height{ 15 };
            static inline const int x_offset{ Bar::width };
        };
        struct DigitGroup
        {
            static inline const int element_width{ 2 * Digit::x_offset + Digit::width };
            static inline const int width{ 6 * element_width };
            static inline const int height{ Digit::height };
        };
        struct FirstDigit : public DigitGroup
        {
            static inline const Point2D start_position{ Margin::left, Margin::bottom };
            static inline const int width{ Digit::width };
        };
        struct Marker
        {
            static inline const int height{ 145 };
            static inline const int y_offset{ bounding_box_height - height };
        };
        struct StartMarker : public Marker
        {
            static inline const Point2D start_position{
                LeftQuietZone::start_position.x + LeftQuietZone::width,
                Margin::bottom + Marker::y_offset
            };
            static inline const int width{ 3 * Bar::width };
        };
        struct DigitBar
        {
            static inline const int width{ 7 * Bar::width };
            static inline const int height{ 135 };
            static inline const int y_offset{ bounding_box_height - height };
        };
        struct DigitBarGroup
        {
            static inline const int width{ 6 * DigitBar::width };
        };
        struct FirstDigitBarGroup : public DigitBarGroup
        {
            static inline const Point2D start_position{
                StartMarker::start_position.x + StartMarker::width,
                Margin::bottom + DigitBar::y_offset
            };
        };
        struct FirstDigitGroup : public DigitGroup
        {
            // First bar group starts with blank, and digits below look better with a 1-bar-width offset
            static inline const Point2D start_position{
                FirstDigitBarGroup::start_position.x + Bar::width,
                Margin::bottom
            };
        };
        struct CenterMarker
        {
            static inline const Point2D start_position{
                FirstDigitBarGroup::start_position.x + FirstDigitBarGroup::width,
                Margin::bottom + Marker::y_offset
            };
            static inline const int width{ 5 * layout::Bar::width };
        };
        struct SecondDigitBarGroup : public DigitBarGroup
        {
            static inline const Point2D start_position{
                CenterMarker::start_position.x + CenterMarker::width,
                Margin::bottom + DigitBar::y_offset
            };
        };
        struct SecondDigitGroup : public DigitGroup
        {
            static inline const Point2D start_position{
                SecondDigitBarGroup::start_position.x,
                Margin::bottom
            };
        };
        struct EndMarker
        {
            static inline const Point2D start_position{
                SecondDigitBarGroup::start_position.x + SecondDigitBarGroup::width,
                Margin::bottom + Marker::y_offset
            };
            static inline const int width{ 3 * layout::Bar::width };
        };
        struct RightQuietZone
        {
            static inline const Point2D start_position{
                EndMarker::start_position.x + EndMarker::width,
                Margin::bottom
            };
            static inline const int width{ 15 };
            static inline const int height{ bounding_box_height };
        };
        struct LMI
        {
            static inline const Point2D start_position{
                EndMarker::start_position.x + EndMarker::width,
                Margin::bottom
            };
            static inline const int width{ 7 * Bar::width };
            static inline const int height{ 12 };
            static inline const int x_offset{ Bar::width };
        };
        struct BoundingBox
        {
            static inline const Point2D start_position{ Margin::left, Margin::bottom };
            static inline const int width{ RightQuietZone::start_position.x + RightQuietZone::width - Margin::left };
            static inline const int height{ bounding_box_height };
        };
        struct Image{
            static inline const Point2D start_position{ 1, 1 };
            static inline const int width{ BoundingBox::start_position.x + BoundingBox::width + Margin::right };
            static inline const int height{ BoundingBox::start_position.y + BoundingBox::height + Margin::top };
        };
    }  // namespace layout


    namespace controls
    {
        struct Base
        {
            virtual void paint(PNGWriter& png_writer) const = 0;
            [[nodiscard]] virtual Point2D get_start_position() const = 0;
            virtual ~Base() {}
        };

        // Bar groups
        //
        struct BarGroup : public Base
        {
            void paint_bar(PNGWriter& png_writer, const Point2D start_position, int width, int height) const
            {
                png_writer.plot_filled_rectangle(
                    rectangle_2d{
                        .bottom_left = { start_position.x, start_position.y },
                        .top_right = { start_position.x + width - 1, start_position.y + height - 1 } },
                        rgb{}
                );
            }

            template <size_t N>
            Point2D paint_bar_group(PNGWriter& png_writer, const std::bitset<N>& bs, Point2D start_position, int width, int height) const
            {
                for (int i{ static_cast<int>(bs.size()) - 1 }; i >= 0; i--)
                {
                    if (bs[i])
                    {
                        paint_bar(png_writer, start_position, width, height);
                    }
                    start_position.x += width;
                }
                return start_position;
            }
        };
        struct StartMarker : public BarGroup
        {
            virtual void paint(PNGWriter& writer) const override
            {
                paint_bar_group(writer, barcode::start_marker, get_start_position(), layout::Bar::width, layout::Marker::height);
            }
            [[nodiscard]] virtual Point2D get_start_position() const override { return layout::StartMarker::start_position; };
        };
        struct CenterMarker : public BarGroup
        {
            virtual void paint(PNGWriter& writer) const override
            {
                paint_bar_group(writer, barcode::center_marker, get_start_position(), layout::Bar::width, layout::Marker::height);
            }
            [[nodiscard]] virtual Point2D get_start_position() const override { return layout::CenterMarker::start_position; };
        };
        struct EndMarker : public BarGroup
        {
            virtual void paint(PNGWriter& writer) const override
            {
                paint_bar_group(writer, barcode::end_marker, get_start_position(), layout::Bar::width, layout::Marker::height);
            }
            [[nodiscard]] virtual Point2D get_start_position() const override { return layout::EndMarker::start_position; };
        };
        struct DigitBarGroup : public BarGroup
        {
            explicit DigitBarGroup(const digit_group_bs& bs) : bs_{ bs } {}
            virtual void paint(PNGWriter& writer) const override
            {
                auto start_position{ get_start_position() };
                for (const auto& digit_bs : bs_)
                {
                    paint_bar_group(writer, digit_bs, start_position, layout::Bar::width, layout::DigitBar::height);
                    start_position.x += layout::DigitGroup::element_width;
                }
            }
        private:
            digit_group_bs bs_{};
        };
        struct FirstDigitBarGroup : public DigitBarGroup
        {
            explicit FirstDigitBarGroup(const digit_group_bs& bs) : DigitBarGroup{ bs } {}
            [[nodiscard]] virtual Point2D get_start_position() const override { return layout::FirstDigitBarGroup::start_position; };
        };
        struct SecondDigitBarGroup : public DigitBarGroup
        {
            explicit SecondDigitBarGroup(const digit_group_bs& bs) : DigitBarGroup{ bs } {}
            [[nodiscard]] virtual Point2D get_start_position() const override { return layout::SecondDigitBarGroup::start_position; };
        };

        // Digit groups
        //
        struct DigitGroup : public Base
        {
        public:
            explicit DigitGroup(const std::string& digit_group) : digit_group_{ digit_group } {}
            virtual void paint(PNGWriter& writer) const override
            {
                const auto font_file_path{ std::filesystem::current_path() / "res" / "fonts" / "calibri.ttf" };
                auto start_position{ get_start_position() };
                for (auto&& digit : digit_group_)
                {
                    writer.plot_text(
                        font_file_path.string(),
                        layout::Digit::height,
                        start_position,
                        0.0,  // angle
                        std::string{ digit },
                        rgb{});

                    start_position.x += layout::DigitGroup::element_width;
                }
            }
        private:
            std::string digit_group_{};
        };
        struct FirstDigit : public DigitGroup
        {
            explicit FirstDigit(const std::string& digit) : DigitGroup{ digit } {}
            [[nodiscard]] virtual Point2D get_start_position() const override { return layout::FirstDigit::start_position; };
        };
        struct FirstDigitGroup : public DigitGroup
        {
            explicit FirstDigitGroup(const std::string& digit_group) : DigitGroup{ digit_group } {}
            [[nodiscard]] virtual Point2D get_start_position() const override { return layout::FirstDigitGroup::start_position; };
        };
        struct SecondDigitGroup : public DigitGroup
        {
            explicit SecondDigitGroup(const std::string& digit_group) : DigitGroup{ digit_group } {}
            [[nodiscard]] virtual Point2D get_start_position() const override { return layout::SecondDigitGroup::start_position; };
        };

        // LMI
        //
        struct LMI : public Base
        {
            virtual void paint(PNGWriter& writer) const override
            {
                // It should be an angle, two lines, but I find a triangle more beautiful
                writer.plot_filled_triangle(
                    { layout::LMI::start_position.x + layout::LMI::x_offset, layout::LMI::start_position.y + layout::LMI::height },
                    { layout::LMI::start_position.x + layout::LMI::width, layout::LMI::start_position.y + layout::LMI::height / 2 },
                    { layout::LMI::start_position.x + layout::LMI::x_offset, layout::LMI::start_position.y },
                    rgb{}
                );
            }
            [[nodiscard]] virtual Point2D get_start_position() const override { return layout::LMI::start_position; };
        };
    }  // namespace controls


    struct generator
    {
        void operator()(const barcode& code, double background_colour, const std::filesystem::path& image_path)
        {
            auto writer = PNGWriter{ layout::Image::width, layout::Image::height, background_colour, image_path.string() };

            std::vector<std::unique_ptr<controls::Base>> vcontrols;

            vcontrols.push_back(std::make_unique<controls::StartMarker>());
            vcontrols.push_back(std::make_unique<controls::CenterMarker>());
            vcontrols.push_back(std::make_unique<controls::EndMarker>());
            vcontrols.push_back(std::make_unique<controls::FirstDigitBarGroup>(code.get_first_digit_group_bs()));
            vcontrols.push_back(std::make_unique<controls::SecondDigitBarGroup>(code.get_second_digit_group_bs()));
            vcontrols.push_back(std::make_unique<controls::FirstDigit>(code.get_first_digit_str()));
            vcontrols.push_back(std::make_unique<controls::FirstDigitGroup>(code.get_first_digit_group_str()));
            vcontrols.push_back(std::make_unique<controls::SecondDigitGroup>(code.get_second_digit_group_str()));
            vcontrols.push_back(std::make_unique<controls::LMI>());

            std::for_each(vcontrols.begin(), vcontrols.end(), [&writer](auto& control_up) { control_up->paint(writer); });
        }
    };
}  // namespace rtc::ean_13::barcode_png


#endif  // EAN_13_BARCODE_PNG_GENERATOR_H
