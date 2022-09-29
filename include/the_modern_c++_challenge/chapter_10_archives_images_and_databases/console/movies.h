#pragma once

#include "chapter_09_data_serialization/movies.h"

#include <chrono>
#include <fmt/ostream.h>
#include <istream>
#include <ostream>
#include <rtc/console.h>
#include <string>  // getline


namespace tmcppc::movies::console {
    inline void from_console(std::istream& is, std::ostream& os, cast& cast) {
        fmt::print(os, "Cast? ('quit' to end the list)\n");
        for (;;) {
            fmt::print(os, "Please enter a star's full name (e.g. Tom Hanks): ");
            std::string star{};
            std::getline(is, star);
            if (star == "quit") {
                break;
            }
            fmt::print(os, "Please enter a role name (e.g. Forrest Gump): ");
            std::string role{};
            std::getline(is, role);
            if (role == "quit") {
                break;
            }
            cast.cast_.push_back({ star, role });
        }
    }

    inline void from_console(std::istream& is, std::ostream& os, writers& writers) {
        fmt::print(os, "Writers? ('quit' to end the list)\n");
        for (;;) {
            fmt::print(os, "Please enter a writer's full name (e.g. Eric Roth): ");
            std::string writer{};
            std::getline(is, writer);
            if (writer == "quit") {
                break;
            }
            writers.writers_.push_back({ writer });
        }
    }

    inline void from_console(std::istream& is, std::ostream& os, directors& directors) {
        fmt::print(os, "Directors? ('quit' to end the list)\n");
        for (;;) {
            fmt::print(os, "Please enter a director's full name (e.g. Robert Zemeckis): ");
            std::string director{};
            std::getline(is, director);
            if (director == "quit") {
                break;
            }
            directors.directors_.push_back({ director });
        }
    }

    inline void from_console(std::istream& is, std::ostream& os, movie& movie) {
        namespace ch = std::chrono;

        fmt::print(os, "Title?\n");
        std::getline(is, movie.title);

        auto current_year{ ch::year_month_day{ ch::floor<ch::days>(ch::system_clock::now()) }.year() };
        fmt::print(os, "Year?\n");
        movie.year = ch::year{static_cast<int>(rtc::console::read_positive_number(is, os,
            "Please enter a number (>= 1900): ", 1900, int(current_year))) };

        fmt::print(os, "Length (in minutes)?\n");
        movie.length = rtc::console::read_positive_number(is, os, "Please enter a number (>= 0): ", 0);

        from_console(is, os, movie.cast);
        from_console(is, os, movie.directors);
        from_console(is, os, movie.writers);
    }
};  // namespace tmcppc::movies::console
