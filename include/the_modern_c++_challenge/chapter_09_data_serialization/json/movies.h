#pragma once

#include "../movies.h"

#include <filesystem>
#include <fstream>  // ifstream, ofstream
#include <nlohmann/json.hpp>
#include <vector>


// nlohmann json requires to_json and from_json functions
// to be in the same namespace as the types it works on
namespace tmcppc::movies {
    // Role
    inline void to_json(nlohmann::json& j, const role& role) {
        j = nlohmann::json{ {"star", role.star}, {"name", role.name} };
    }
    inline void from_json(const nlohmann::json& j, role& role) {
        j.at("star").get_to(role.star);
        j.at("name").get_to(role.name);
    }

    // Cast
    inline void to_json(nlohmann::json& j, const cast& cast) {
        j = cast.cast_;
    }
    inline void from_json(const nlohmann::json& j, cast& cast) {
        cast.cast_ = j.get<std::vector<role>>();
    }

    // Director
    inline void to_json(nlohmann::json& j, const director& director) {
        j = director.name;
    }
    inline void from_json(const nlohmann::json& j, director& director) {
        j.get_to(director.name);
    }

    // Directors
    inline void to_json(nlohmann::json& j, const directors& directors) {
        j = directors.directors_;
    }
    inline void from_json(const nlohmann::json& j, directors& directors) {
        directors.directors_ = j.get<std::vector<director>>();
    }

    // Writer
    inline void to_json(nlohmann::json& j, const writer& writer) {
        j = writer.name;
    }
    inline void from_json(const nlohmann::json& j, writer& writer) {
        j.get_to(writer.name);
    }

    // Writers
    inline void to_json(nlohmann::json& j, const writers& writers) {
        j = writers.writers_;
    }
    inline void from_json(const nlohmann::json& j, writers& writers) {
        writers.writers_ = j.get<std::vector<writer>>();
    }

    // Movie
    inline void to_json(nlohmann::json& j, const movie& movie) {
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
    inline void from_json(const nlohmann::json& j, movie& movie) {
        j.at("id").get_to(movie.id);
        j.at("title").get_to(movie.title);
        movie.year = std::chrono::year{ j.at("year").get<int>() };
        j.at("length").get_to(movie.length);
        j.at("cast").get_to(movie.cast);
        j.at("directors").get_to(movie.directors);
        j.at("writers").get_to(movie.writers);
    }

    // Catalog
    inline void to_json(nlohmann::json& j, const catalog& catalog) {
        j = catalog.movies;
    }
    inline void from_json(const nlohmann::json& j, catalog& catalog) {
        catalog.movies = j.get<std::vector<movie>>();
    }

    // JSON document
    struct doc {
        catalog catalog_{};

        doc() = default;
        explicit doc(const catalog& c) : catalog_{ c } {}

        void save_to(const std::filesystem::path& output_file_path) {
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
