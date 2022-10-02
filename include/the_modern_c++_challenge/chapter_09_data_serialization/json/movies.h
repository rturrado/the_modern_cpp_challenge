#pragma once

#include "../movies.h"

#include <filesystem>
#include <fstream>  // ifstream, ofstream
#include <nlohmann/json.hpp>
#include <utility>
#include <vector>


// nlohmann json requires to_json and from_json functions
// to be in the same namespace as the types it works on
namespace tmcppc::movies {
    // Role
    inline void to_json(nlohmann::json& j, const role_t& role) {
        j = nlohmann::json{ {"star", role.star}, {"name", role.name} };
    }
    inline void from_json(const nlohmann::json& j, role_t& role) {
        j.at("star").get_to(role.star);
        j.at("name").get_to(role.name);
    }

    // Cast
    inline void to_json(nlohmann::json& j, const cast_t& cast) {
        j = cast.data;
    }
    inline void from_json(const nlohmann::json& j, cast_t& cast) {
        cast.data = j.get<std::vector<role_t>>();
    }

    // Director
    inline void to_json(nlohmann::json& j, const director_t& director) {
        j = director.name;
    }
    inline void from_json(const nlohmann::json& j, director_t& director) {
        j.get_to(director.name);
    }

    // Directors
    inline void to_json(nlohmann::json& j, const directors_t& directors) {
        j = directors.data;
    }
    inline void from_json(const nlohmann::json& j, directors_t& directors) {
        directors.data = j.get<std::vector<director_t>>();
    }

    // Writer
    inline void to_json(nlohmann::json& j, const writer_t& writer) {
        j = writer.name;
    }
    inline void from_json(const nlohmann::json& j, writer_t& writer) {
        j.get_to(writer.name);
    }

    // Writers
    inline void to_json(nlohmann::json& j, const writers_t& writers) {
        j = writers.data;
    }
    inline void from_json(const nlohmann::json& j, writers_t& writers) {
        writers.data = j.get<std::vector<writer_t>>();
    }

    // Movie
    inline void to_json(nlohmann::json& j, const movie_t& movie) {
        j = nlohmann::json{
            { "id", movie.id },
            { "title", movie.title },
            { "year", int(movie.year) },
            { "length", movie.length },
            { "cast", movie.cast },
            { "directors", movie.directors },
            { "writers", movie.writers }
        };
    }
    inline void from_json(const nlohmann::json& j, movie_t& movie) {
        j.at("id").get_to(movie.id);
        j.at("title").get_to(movie.title);
        movie.year = std::chrono::year{ j.at("year").get<int>() };
        j.at("length").get_to(movie.length);
        j.at("cast").get_to(movie.cast);
        j.at("directors").get_to(movie.directors);
        j.at("writers").get_to(movie.writers);
    }

    // Catalog
    inline void to_json(nlohmann::json& j, const catalog_t& catalog) {
        j = catalog.movies;
    }
    inline void from_json(const nlohmann::json& j, catalog_t& catalog) {
        catalog.movies = j.get<std::vector<movie_t>>();
    }

    // JSON document
    struct doc {
        catalog_t catalog_{};

        doc() = default;
        explicit doc(catalog_t c) : catalog_{ std::move(c) } {}

        void save_to(const std::filesystem::path& output_file_path) const {
            std::ofstream ofs{ output_file_path };
            nlohmann::json j{};
            to_json(j, catalog_);
            ofs << std::setw(4) << j << "\n";
        }
        void load_from(const std::filesystem::path& input_file_path) {
            std::ifstream ifs{ input_file_path };
            nlohmann::json j{};
            ifs >> j;
            from_json(j, catalog_);
        }
    };
    inline bool operator==(const doc& lhs, const doc& rhs) {
        return lhs.catalog_ == rhs.catalog_;
    }
}  // namespace tmcppc::movies
