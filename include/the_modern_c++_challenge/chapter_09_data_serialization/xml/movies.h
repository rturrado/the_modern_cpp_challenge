#pragma once

#include "../movies.h"
#include "pugixml_wrapper.h"

#include <chrono>
#include <filesystem>
#include <pugixml.hpp>
#include <utility>


namespace tmcppc::movies::xml {
    // Role
    inline void to_xml(pugi::xml_node& root, const role_t& role) {
        tmcppc::pugixml::append_attribute_or_throw(root, "star") = role.star.c_str();
        tmcppc::pugixml::append_attribute_or_throw(root, "name") = role.name.c_str();
    }
    inline void from_xml(const pugi::xml_node& root, role_t& role) {
        role.star = tmcppc::pugixml::attribute_or_throw(root, "star").as_string();
        role.name = tmcppc::pugixml::attribute_or_throw(root, "name").as_string();
    }

    // Cast
    inline void to_xml(pugi::xml_node& root, const cast_t& cast) {
        for (auto&& role : cast.data) {
            auto node{ tmcppc::pugixml::append_child_or_throw(root, "role") };
            to_xml(node, role);
        }
    }
    inline void from_xml(const pugi::xml_node& root, cast_t& cast) {
        for (auto&& node : root.children("role")) {
            role_t role{};
            from_xml(node, role);
            cast.data.push_back(role);
        }
    }

    // Director
    inline void to_xml(pugi::xml_node& root, const director_t& director) {
        tmcppc::pugixml::append_attribute_or_throw(root, "name") = director.name.c_str();
    }
    inline void from_xml(const pugi::xml_node& root, director_t& director) {
        director.name = tmcppc::pugixml::attribute_or_throw(root, "name").as_string();
    }

    // Directors
    inline void to_xml(pugi::xml_node& root, const directors_t& directors) {
        for (auto&& director : directors.data) {
            auto node{ tmcppc::pugixml::append_child_or_throw(root, "director") };
            to_xml(node, director);
        }
    }
    inline void from_xml(const pugi::xml_node& root, directors_t& directors) {
        for (auto&& node : root.children("director")) {
            director_t director{};
            from_xml(node, director);
            directors.data.push_back(director);
        }
    }

    // Writer
    inline void to_xml(pugi::xml_node& root, const writer_t& writer) {
        tmcppc::pugixml::append_attribute_or_throw(root, "name") = writer.name.c_str();
    }
    inline void from_xml(const pugi::xml_node& root, writer_t& writer) {
        writer.name = tmcppc::pugixml::attribute_or_throw(root, "name").as_string();
    }

    // Writers
    inline void to_xml(pugi::xml_node& root, const writers_t& writers) {
        for (auto&& writer : writers.data) {
            auto node{ tmcppc::pugixml::append_child_or_throw(root, "writer") };
            to_xml(node, writer);
        }
    }
    inline void from_xml(const pugi::xml_node& root, writers_t& writers) {
        for (auto&& node : root.children("writer")) {
            writer_t writer{};
            from_xml(node, writer);
            writers.data.push_back(writer);
        }
    }

    // Movie
    inline void to_xml(pugi::xml_node& root, const movie_t& movie) {
        using namespace tmcppc::pugixml;

        append_attribute_or_throw(root, "id") = movie.id;
        append_attribute_or_throw(root, "title") = movie.title.c_str();
        append_attribute_or_throw(root, "year") = int(movie.year);
        append_attribute_or_throw(root, "length") = movie.length;
        {
            auto node{ append_child_or_throw(root, "cast") };
            to_xml(node, movie.cast);
        }
        {
            auto node{ append_child_or_throw(root, "directors") };
            to_xml(node, movie.directors);
        }
        {
            auto node{ append_child_or_throw(root, "writers")};
            to_xml(node, movie.writers);
        }
    }
    inline void from_xml(const pugi::xml_node& root, movie_t& movie) {
        using namespace tmcppc::pugixml;

        movie.id = attribute_or_throw(root, "id").as_uint();
        movie.title = attribute_or_throw(root, "title").as_string();
        movie.year = std::chrono::year{ attribute_or_throw(root, "year").as_int() };
        movie.length = attribute_or_throw(root, "length").as_uint();
        from_xml(child_or_throw(root, "cast"), movie.cast);
        from_xml(child_or_throw(root, "directors"), movie.directors);
        from_xml(child_or_throw(root, "writers"), movie.writers);
    }

    // Catalog
    inline void to_xml(pugi::xml_node& root, const catalog_t& catalog) {
        for (auto&& movie : catalog.movies) {
            auto node{ tmcppc::pugixml::append_child_or_throw(root, "movie") };
            to_xml(node, movie);
        }
    }
    inline void from_xml(const pugi::xml_node& root, catalog_t& catalog) {
        for (auto&& node : root.children("movie")) {
            movie_t movie{};
            from_xml(node, movie);
            catalog.movies.push_back(movie);
        }
    }

    // doc
    struct doc {
        catalog_t catalog_{};

        doc() = default;
        explicit doc(catalog_t c) : catalog_{ std::move(c) } {}

        [[nodiscard]] pugi::xml_node get_pugi_xml_root() const { return pugi_xml_doc_.root(); }

        void save_to(const std::filesystem::path& output_file_path) {
            auto node{ tmcppc::pugixml::append_child_or_throw(pugi_xml_doc_, "movies") };
            to_xml(node, catalog_);

            tmcppc::pugixml::save_xml_document_to_file_or_throw(pugi_xml_doc_, output_file_path.string().c_str());
        }
        void load_from(const std::filesystem::path& input_file_path) {
            tmcppc::pugixml::load_xml_document_from_file_or_throw(pugi_xml_doc_, input_file_path.string().c_str());

            from_xml(tmcppc::pugixml::child_or_throw(pugi_xml_doc_, "movies"), catalog_);
        }

    private:
        // doc_ should be used as a cache, but it isn't at the moment
        // We load from file to doc_, and then from doc_ to the different structs
        // We save from the different structs to doc_, and then to file
        // We never check if the structs contents have changed, to avoid writing to doc_ and even to file
        // That same check would be mandatory before querying doc_ directly, once loaded (e.g. problem 74)
        pugi::xml_document pugi_xml_doc_{};
    };
    inline bool operator==(const doc& lhs, const doc& rhs) { return lhs.catalog_ == rhs.catalog_; }
}  // namespace tmcppc::movies::xml
