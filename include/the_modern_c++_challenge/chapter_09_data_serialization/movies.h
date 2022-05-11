#pragma once

#include "rtc/pretty_print.h"

#include <chrono>
#include <fmt/ostream.h>
#include <filesystem>
#include <optional>
#include <ostream>
#include <string>
#include <vector>


namespace tmcppc::movies {
    using namespace rtc::pretty_print;
    namespace fs = std::filesystem;

    struct role {
        std::string star{};
        std::string name{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}{} ({})", indentation, star, name);
        }
        auto operator<=>(const role& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const role& role) {
        role.print(os);
        return os;
    }

    struct cast {
        std::vector<role> cast_{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}Cast:\n", indentation);
            for (const auto& role : cast_) {
                role.print(os, indentation + 1);
                fmt::print(os, "\n");
            }
        }
        auto operator<=>(const cast& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const cast& cast) {
        cast.print(os);
        return os;
    }

    struct director {
        std::string name{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}{}", indentation, name);
        }
        auto operator<=>(const director& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const director& director) {
        director.print(os);
        return os;
    }

    struct directors {
        std::vector<director> directors_{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}Directors:\n", indentation);
            for (const auto& director : directors_) {
                director.print(os, indentation + 1);
                fmt::print(os, "\n");
            }
        }
        auto operator<=>(const directors& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const directors& directors) {
        directors.print(os);
        return os;
    }


    struct writer {
        std::string name{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}{}", indentation, name);
        }
        auto operator<=>(const writer& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const writer& writer) {
        writer.print(os);
        return os;
    }

    struct writers {
        std::vector<writer> writers_{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}Writers:\n", indentation);
            for (const auto& writer : writers_) {
                writer.print(os, indentation + 1);
                fmt::print(os, "\n");
            }
        }
        auto operator<=>(const writers& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const writers& writers) {
        writers.print(os);
        return os;
    }

    struct MediaFile {
        size_t id{};
        fs::path file_path{};
        std::optional<std::string> description{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}Media file:\n", indentation);
            fmt::print(os, "{}id: {}\n", indentation + 1, id);
            fmt::print(os, "{}path: '{}'\n", indentation + 1, file_path.generic_string());
            fmt::print(os, "{}description: '{}'\n", indentation + 1, description.value_or(""));
        }
        auto operator<=>(const MediaFile& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const MediaFile& media_file) {
        media_file.print(os);
        return os;
    }

    struct media_files {
        std::vector<MediaFile> media_files_{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}Media files:\n", indentation);
            for (const auto& media_file : media_files_) {
                media_file.print(os, indentation + 1);
            }
        }
        auto operator<=>(const media_files& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const media_files& media_files) {
        media_files.print(os);
        return os;
    }

    struct movie {
        size_t id{};
        std::string title{};
        std::chrono::year year{};
        size_t length{};
        cast cast{};
        directors directors{};
        writers writers{};
        media_files media_files{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}Movie:\n", indentation);
            fmt::print(os, "{}id: {}\n", indentation + 1, id);
            fmt::print(os, "{}title: {}\n", indentation + 1, title);
            fmt::print(os, "{}year: {}\n", indentation + 1, static_cast<int>(year));
            fmt::print(os, "{}length: {}\n", indentation + 1, length);
            cast.print(os, indentation + 1);
            directors.print(os, indentation + 1);
            writers.print(os, indentation + 1);
            media_files.print(os, indentation + 1);
        }
        auto operator<=>(const movie& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const movie& movie) {
        movie.print(os);
        return os;
    }

    struct catalog {
        std::vector<movie> movies{};

        void print(std::ostream& os, const indentation& indentation = {}) const noexcept {
            fmt::print(os, "{}Catalog:\n", indentation);
            for (const auto& movie : movies) {
                movie.print(os, indentation + 1);
            }
        }
        auto operator<=>(const catalog& other) const = default;
    };
    inline std::ostream& operator<<(std::ostream& os, const catalog& catalog) {
        catalog.print(os);
        return os;
    }
}  // namespace tmcppc::movies


template <>
struct fmt::formatter<tmcppc::movies::catalog> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::catalog& catalog, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        catalog.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};
