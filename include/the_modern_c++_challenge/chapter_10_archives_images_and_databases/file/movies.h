#pragma once

#include "chapter_09_data_serialization/movies.h"

#include <chrono>
#include <fstream>  // ifstream
#include <string>  // getline, stoi


namespace tmcppc::movies::file {
    inline void from_file(std::ifstream& ifs, cast_t& cast) {
        std::string line{};
        std::getline(ifs, line);
        int number_of_roles{ std::stoi(line) };
        while (number_of_roles--) {
            std::string star{};
            std::string role{};
            std::getline(ifs, star);
            std::getline(ifs, role);
            cast.data.emplace_back(star, role);
        }
    }

    inline void from_file(std::ifstream& ifs, writers_t& writers) {
        std::string line{};
        std::getline(ifs, line);
        int number_of_writers{ std::stoi(line) };
        while (number_of_writers--) {
            std::getline(ifs, line);
            writers.data.emplace_back(line);
        }
    }

    inline void from_file(std::ifstream& ifs, directors_t& directors) {
        std::string line{};
        std::getline(ifs, line);
        int number_of_directors{ std::stoi(line) };
        while (number_of_directors--) {
            std::getline(ifs, line);
            directors.data.emplace_back(line);
        }
    }

    inline void from_file(std::ifstream& ifs, movie_t& movie) {
        namespace ch = std::chrono;

        std::getline(ifs, movie.title);

        std::string line{};
        std::getline(ifs, line);
        movie.year = ch::year{ std::stoi(line) };

        std::getline(ifs, line);
        movie.length = std::stoi(line);

        from_file(ifs, movie.cast);
        from_file(ifs, movie.directors);
        from_file(ifs, movie.writers);
    }
}  // namespace tmcppc::movies::file
