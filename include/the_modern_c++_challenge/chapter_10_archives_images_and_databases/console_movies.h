#ifndef CONSOLE_MOVIES_H
#define CONSOLE_MOVIES_H

#include "chapter_09_data_serialization/movies.h"

#include "rtc/console.h"

#include <chrono>
#include <iostream>  // cout
#include <string>  // getline


namespace tmcppc::movies::console
{
    inline void from_console(cast& cast)
    {
        std::cout << "Cast? ('quit' to end the list)?\n";
        for (;;)
        {
            std::cout << "Please enter a star's full name (e.g. Tom Hanks): ";
            std::string star{};
            std::getline(std::cin, star);
            if (star == "quit") { break; }
            std::cout << "Please enter a role name (e.g. Forrest Gump): ";
            std::string role{};
            std::getline(std::cin, role);
            if (role == "quit") { break; }
            cast.cast.push_back({ star, role });
        }
    }

    inline void from_console(writers& writers)
    {
        std::cout << "Writers? ('quit' to end the list)\n";
        for (;;)
        {
            std::cout << "Please enter a writer's full name (e.g. Eric Roth): ";
            std::string writer{};
            std::getline(std::cin, writer);
            if (writer == "quit") { break; }
            writers.writers.push_back({ writer });
        }
    }

    inline void from_console(directors& directors)
    {
        std::cout << "Directors? ('quit' to end the list)\n";
        for (;;)
        {
            std::cout << "Please enter a director's full name (e.g. Robert Zemeckis): ";
            std::string director{};
            std::getline(std::cin, director);
            if (director == "quit") { break; }
            directors.directors.push_back({ director });
        }
    }

    inline void from_console(movie& movie)
    {
        namespace ch = std::chrono;

        std::cout << "ID?\n";
        movie.id = read_positive_number("Please enter a number (starting from 0): ", 0);

        std::cout << "Title?\n";
        std::getline(std::cin, movie.title);

        auto current_year{ ch::year_month_day{ ch::floor<ch::days>(ch::system_clock::now()) }.year() };
        std::cout << "Year?\n";
        movie.year = ch::year{ static_cast<int>(read_positive_number("Please enter a number (starting from 1900): ", 1900, static_cast<int>(current_year))) };

        std::cout << "Length (in minutes)?\n";
        movie.length = read_positive_number("Please enter a number (starting from 0): ", 0);

        from_console(movie.cast);
        from_console(movie.directors);
        from_console(movie.writers);
    }
};  // namespace tmcppc::movies::console


#endif  // CONSOLE_MOVIES_H
