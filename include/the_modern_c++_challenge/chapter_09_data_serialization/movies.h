#pragma once

#include "rtc/pretty_print.h"

#include <chrono>
#include <cstdint>  // int64_t
#include "fmt/ostream.h"
#include <filesystem>
#include <optional>
#include <ostream>
#include <sstream>  // ostringstream
#include <string>
#include <vector>


namespace tmcppc::movies {
    using indentation = rtc::pretty_print::indentation;

    // Role
    struct role_t {
        std::string star{};
        std::string name{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}{} ({})", indentation, star, name);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const noexcept {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const role_t& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const role_t& role) {
        role.print(os);
        return os;
    }

    // Cast
    struct cast_t {
        std::vector<role_t> data{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            if (data.empty()) {
                fmt::print(os, "{}Cast: []", indentation);
            } else {
                fmt::print(os, "{}Cast:", indentation);
                for (const auto& role : data) {
                    fmt::print(os, "\n");
                    role.print(os, indentation + 1);
                }
            }
        }
        void println(std::ostream& os, const indentation& indentation = {}) const noexcept {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const cast_t& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const cast_t& cast) {
        cast.print(os);
        return os;
    }

    // Director
    struct director_t {
        std::string name{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}{}", indentation, name);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const noexcept {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const director_t& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const director_t& director) {
        director.print(os);
        return os;
    }

    // Directors
    struct directors_t {
        std::vector<director_t> data{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            if (data.empty()) {
                fmt::print(os, "{}Directors: []", indentation);
            } else {
                fmt::print(os, "{}Directors:", indentation);
                for (const auto& director : data) {
                    fmt::print(os, "\n");
                    director.print(os, indentation + 1);
                }
            }
        }
        void println(std::ostream& os, const indentation& indentation = {}) const noexcept {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const directors_t& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const directors_t& directors) {
        directors.print(os);
        return os;
    }

    // Writer
    struct writer_t {
        std::string name{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}{}", indentation, name);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const noexcept {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const writer_t& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const writer_t& writer) {
        writer.print(os);
        return os;
    }

    // Writers
    struct writers_t {
        std::vector<writer_t> data{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            if (data.empty()) {
                fmt::print(os, "{}Writers: []", indentation);
            } else {
                fmt::print(os, "{}Writers:", indentation);
                for (const auto& writer : data) {
                    fmt::print(os, "\n");
                    writer.print(os, indentation + 1);
                }
            }
        }
        void println(std::ostream& os, const indentation& indentation = {}) const noexcept {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const writers_t& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const writers_t& writers) {
        writers.print(os);
        return os;
    }

    // Media file
    struct media_file_t {
        std::int64_t id{};
        std::filesystem::path file_path{};
        std::optional<std::string> description{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}Media file:\n", indentation);
            fmt::print(os, "{}id: {}\n", indentation + 1, id);
            fmt::print(os, "{}path: '{}'\n", indentation + 1, file_path.generic_string());
            fmt::print(os, "{}description: '{}'", indentation + 1, description.value_or(""));
        }
        void println(std::ostream& os, const indentation& indentation = {}) const noexcept {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator==(const media_file_t& other) const {
            return
                id == other.id and
                file_path.generic_string() == other.file_path.generic_string() and
                description.value_or("") == other.description.value_or("");
        }
        auto operator<(const media_file_t& other) const {
            return
                id < other.id or
                    (id == other.id and
                        (file_path.generic_string() < other.file_path.generic_string() or
                            (file_path.generic_string() == other.file_path.generic_string() and
                             description.value_or("") < other.description.value_or(""))));
        }
        auto operator>(const media_file_t& other) const {
            return
                id > other.id or
                (id == other.id and
                    (file_path.generic_string() > other.file_path.generic_string() or
                        (file_path.generic_string() == other.file_path.generic_string() and
                            description.value_or("") > other.description.value_or(""))));
        }
        auto operator!=(const media_file_t& other) const {
            return not (*this == other);
        }
        auto operator<=(const media_file_t& other) const {
            return not (*this > other);
        }
        auto operator>=(const media_file_t& other) const {
            return not (*this < other);
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const media_file_t& media_file) {
        media_file.print(os);
        return os;
    }

    // Media files
    struct media_files_t {
        std::vector<media_file_t> data{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            if (data.empty()) {
                fmt::print(os, "{}Media files: []", indentation);
            } else {
                fmt::print(os, "{}Media files:", indentation);
                for (const auto& media_file : data) {
                    fmt::print(os, "\n");
                    media_file.print(os, indentation + 1);
                }
            }
        }
        void println(std::ostream& os, const indentation& indentation = {}) const noexcept {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const media_files_t& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const media_files_t& media_files) {
        media_files.print(os);
        return os;
    }

    // Movie
    struct movie_t {
        std::int64_t id{};
        std::string title{};
        std::chrono::year year{};
        size_t length{};
        cast_t cast{};
        directors_t directors{};
        writers_t writers{};
        media_files_t media_files{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}Movie:\n", indentation);
            fmt::print(os, "{}id: {}\n", indentation + 1, id);
            fmt::print(os, "{}title: {}\n", indentation + 1, title);
            fmt::print(os, "{}year: {}\n", indentation + 1, int(year));
            fmt::print(os, "{}length: {}\n", indentation + 1, length);
            cast.println(os, indentation + 1);
            directors.println(os, indentation + 1);
            writers.println(os, indentation + 1);
            media_files.print(os, indentation + 1);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const noexcept {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const movie_t& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const movie_t& movie) {
        movie.print(os);
        return os;
    }

    // Catalog
    struct catalog_t {
        std::vector<movie_t> movies{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            if (movies.empty()) {
                fmt::print(os, "{}Catalog: []", indentation);
            } else {
                fmt::print(os, "{}Catalog:", indentation);
                for (const auto& movie : movies) {
                    fmt::print(os, "\n");
                    movie.print(os, indentation + 1);
                }
            }
        }
        void println(std::ostream& os, const indentation& indentation = {}) const noexcept {
            print(os, indentation);
            fmt::print(os, "\n");
        }
        auto operator<=>(const catalog_t& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const catalog_t& catalog) {
        catalog.print(os);
        return os;
    }
}  // namespace tmcppc::movies


template <>
struct fmt::formatter<tmcppc::movies::role_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::role_t& role, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        role.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::movies::cast_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::cast_t& cast, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        cast.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::movies::writer_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::writer_t& writer, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        writer.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::movies::writers_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::writers_t& writers, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        writers.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::movies::director_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::director_t& director, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        director.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::movies::directors_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::directors_t& directors, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        directors.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::movies::media_file_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::media_file_t& media_file, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        media_file.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::movies::media_files_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::media_files_t& media_files, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        media_files.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::movies::movie_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::movie_t& movie, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        movie.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::movies::catalog_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::catalog_t& catalog, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        catalog.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};
