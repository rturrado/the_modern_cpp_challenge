#pragma once

#include <fmt/ostream.h>
#include <ostream>
#include <rtc/pretty_print.h>
#include <sstream>  // ostringstream
#include <vector>


namespace tmcppc::face_detection {
    // Error
    struct error {
        std::string code{};
        std::string message{};

        void print(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            fmt::print(os, "{}(code: {}, message: '{}')", indentation, code, message);
        }
        void println(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const error& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const error& error) {
        error.print(os);
        return os;
    }

    // Error response
    struct error_response {
        error error_{};

        void print(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            fmt::print(os, "{}Error: ", indentation);
            error_.print(os);
        }
        void println(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const error_response& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const error_response& error_response) {
        error_response.print(os);
        return os;
    }

    // Point
    struct point {
        double x{};
        double y{};

        void print(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            fmt::print(os, "{}(x: {:.1f}, y: {:.1f})", indentation, x, y);
        }
        void println(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const point& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const point& point) {
        point.print(os);
        return os;
    }

    // Rectangle
    struct rectangle {
        double top{};
        double left{};
        double width{};
        double height{};

        void print(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            fmt::print(os, "{}(top: {:.1f}, left: {:.1f}, width: {:.1f}, height: {:.1f})",
                indentation, top, left, width, height);
        }
        void println(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const rectangle& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const rectangle& rectangle) {
        rectangle.print(os);
        return os;
    }

    // Face landmarks
    struct face_landmarks {
        point pupil_left{};
        point pupil_right{};
        point nose_tip{};
        point mouth_left{};
        point mouth_right{};
        point eyebrow_left_outer{};
        point eyebrow_left_inner{};
        point eye_left_outer{};
        point eye_left_top{};
        point eye_left_bottom{};
        point eye_left_inner{};
        point eyebrow_right_inner{};
        point eyebrow_right_outer{};
        point eye_right_inner{};
        point eye_right_top{};
        point eye_right_bottom{};
        point eye_right_outer{};
        point nose_root_left{};
        point nose_root_right{};
        point nose_left_alar_top{};
        point nose_right_alar_top{};
        point nose_left_alar_out_tip{};
        point nose_right_alar_out_tip{};
        point upper_lip_top{};
        point upper_lip_bottom{};
        point under_lip_top{};
        point under_lip_bottom{};

        void print(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            fmt::print(os, "{}Face landmarks:\n", indentation);
            fmt::print(os, "{}Pupil left: ", indentation + 1);
            pupil_left.println(os);
            fmt::print(os, "{}Pupil right: ", indentation + 1);
            pupil_right.println(os);
            fmt::print(os, "{}Nose tip: ", indentation + 1);
            nose_tip.println(os);
            fmt::print(os, "{}Mouth left: ", indentation + 1);
            mouth_left.println(os);
            fmt::print(os, "{}Mouth right: ", indentation + 1);
            mouth_right.println(os);
            fmt::print(os, "{}Eyebrow left outer: ", indentation + 1);
            eyebrow_left_outer.println(os);
            fmt::print(os, "{}Eyebrow left inner: ", indentation + 1);
            eyebrow_left_inner.println(os);
            fmt::print(os, "{}Eye left outer: ", indentation + 1);
            eye_left_outer.println(os);
            fmt::print(os, "{}Eye left top: ", indentation + 1);
            eye_left_top.println(os);
            fmt::print(os, "{}Eye left bottom: ", indentation + 1);
            eye_left_bottom.println(os);
            fmt::print(os, "{}Eye left inner: ", indentation + 1);
            eye_left_inner.println(os);
            fmt::print(os, "{}Eyebrow right inner: ", indentation + 1);
            eyebrow_right_inner.println(os);
            fmt::print(os, "{}Eyebrow right outer: ", indentation + 1);
            eyebrow_right_outer.println(os);
            fmt::print(os, "{}Eye right inner: ", indentation + 1);
            eye_right_inner.println(os);
            fmt::print(os, "{}Eye right top: ", indentation + 1);
            eye_right_top.println(os);
            fmt::print(os, "{}Eye right bottom: ", indentation + 1);
            eye_right_bottom.println(os);
            fmt::print(os, "{}Eye right outer: ", indentation + 1);
            eye_right_outer.println(os);
            fmt::print(os, "{}Nose root left: ", indentation + 1);
            nose_root_left.println(os);
            fmt::print(os, "{}Nose root right: ", indentation + 1);
            nose_root_right.println(os);
            fmt::print(os, "{}Nose left alar top: ", indentation + 1);
            nose_left_alar_top.println(os);
            fmt::print(os, "{}Nose right alar top: ", indentation + 1);
            nose_right_alar_top.println(os);
            fmt::print(os, "{}Nose left alar out tip: ", indentation + 1);
            nose_left_alar_out_tip.println(os);
            fmt::print(os, "{}Nose right alar out tip: ", indentation + 1);
            nose_right_alar_out_tip.println(os);
            fmt::print(os, "{}Upper lip top: ", indentation + 1);
            upper_lip_top.println(os);
            fmt::print(os, "{}Upper lip bottom: ", indentation + 1);
            upper_lip_bottom.println(os);
            fmt::print(os, "{}Under lip top: ", indentation + 1);
            under_lip_top.println(os);
            fmt::print(os, "{}Under lip bottom: ", indentation + 1);
            under_lip_bottom.print(os);
        }
        void println(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const face_landmarks& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const face_landmarks& face_landmarks) {
        face_landmarks.print(os);
        return os;
    }

    // Emotion
    struct emotion {
        double anger{};
        double contempt{};
        double disgust{};
        double fear{};
        double happiness{};
        double neutral{};
        double sadness{};
        double surprise{};

        void print(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            fmt::print(os, "{}Emotion:\n", indentation);
            fmt::print(os, "{}Anger: {:.3f}\n", indentation + 1, anger);
            fmt::print(os, "{}Contempt: {:.3f}\n", indentation + 1, contempt);
            fmt::print(os, "{}Disgust: {:.3f}\n", indentation + 1, disgust);
            fmt::print(os, "{}Fear: {:.3f}\n", indentation + 1, fear);
            fmt::print(os, "{}Happiness: {:.3f}\n", indentation + 1, happiness);
            fmt::print(os, "{}Neutral: {:.3f}\n", indentation + 1, neutral);
            fmt::print(os, "{}Sadness: {:.3f}\n", indentation + 1, sadness);
            fmt::print(os, "{}Surprise: {:.3f}", indentation + 1, surprise);
        }
        void println(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const emotion& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const emotion& emotion) {
        emotion.print(os);
        return os;
    }

    // Face attributes
    struct face_attributes {
        std::string gender{};
        double age{};
        emotion emotion_{};

        void print(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            fmt::print(os, "{}Face attributes:\n", indentation);
            fmt::print(os, "{}Gender: {}\n", indentation + 1, gender);
            fmt::print(os, "{}Age: {:.1f}\n", indentation + 1, age);
            emotion_.print(os, indentation + 1);
        }
        void println(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const face_attributes& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const face_attributes& face_attributes) {
        face_attributes.print(os);
        return os;
    }

    // Face
    struct face {
        std::string id{};
        rectangle rectangle{};
        face_landmarks landmarks{};
        face_attributes attributes{};

        void print(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            fmt::print(os, "{}Face:\n", indentation);
            fmt::print(os, "{}ID: {}\n", indentation + 1, id);
            fmt::print(os, "{}Rectangle: ", indentation + 1);
            rectangle.println(os);
            landmarks.println(os, indentation + 1);
            attributes.print(os, indentation + 1);
        }
        void println(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const face& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const face& face) {
        face.print(os);
        return os;
    }

    // Faces response
    struct faces_response {
        std::vector<face> faces{};

        void print(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            if (faces.empty()) {
                fmt::print("{}Faces: []", indentation);
            } else {
                fmt::print(os, "{}Faces:", indentation);
                for (auto&& face : faces) {
                    fmt::print(os, "\n");
                    face.print(os, indentation + 1);
                }
            }
        }
        void println(std::ostream& os, const rtc::pretty_print::indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const faces_response& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const faces_response& faces_response) {
        faces_response.print(os);
        return os;
    }
}  // namespace tmcppc::face_detection


template <>
struct fmt::formatter<tmcppc::face_detection::error> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::error& error, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        error.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::error_response> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::error_response& error_response, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        error_response.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::point> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::point& point, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        point.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::rectangle> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::rectangle& rectangle, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        rectangle.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::face_landmarks> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::face_landmarks& face_landmarks, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        face_landmarks.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::emotion> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::emotion& emotion, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        emotion.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::face_attributes> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::face_attributes& face_attributes, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        face_attributes.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::face> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::face& face, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        face.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::faces_response> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::faces_response& faces_response, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        faces_response.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};
