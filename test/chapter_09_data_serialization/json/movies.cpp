#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies/samples.h"
#include "chapter_09_data_serialization/json/movies.h"

#include "nlohmann/json.hpp"

#include "gtest/gtest.h"

#include <sstream>  // ostringstream

using namespace std::chrono_literals;
using namespace tmcppc::movies;


// Role
TEST(json_role, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, samples::role);
    role_t r{};
    from_json(j, r);
    EXPECT_EQ(samples::role, r);
}

// Cast
TEST(json_cast, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, samples::cast);
    cast_t c{};
    from_json(j, c);
    EXPECT_EQ(samples::cast, c);
}

// Director
TEST(json_director, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, samples::director);
    director_t d{};
    from_json(j, d);
    EXPECT_EQ(samples::director, d);
}

// Directors
TEST(json_directors, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, samples::directors);
    directors_t ds{};
    from_json(j, ds);
    EXPECT_EQ(samples::directors, ds);
}

// Writer
TEST(json_writer, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, samples::writer);
    writer_t w{};
    from_json(j, w);
    EXPECT_EQ(samples::writer, w);
}

// Writers
TEST(json_writers, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, samples::writers);
    writers_t ws{};
    from_json(j, ws);
    EXPECT_EQ(samples::writers, ws);
}

// Movie
TEST(json_movie, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, samples::movie);
    movie_t mv{};
    from_json(j, mv);
    EXPECT_EQ(samples::movie, mv);
}

// Catalog
TEST(json_catalog, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, samples::catalog);
    catalog_t c{};
    from_json(j, c);
    EXPECT_EQ(samples::catalog, c);
}

// JSON document
TEST(json_doc, save_to_and_load_from) {
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "test_doc_save_to_and_load_from.json" };
    doc out_doc{ samples::catalog };
    out_doc.save_to(temp_file_path);
    doc in_doc{};
    in_doc.load_from(temp_file_path);
    EXPECT_EQ(out_doc, in_doc);
}
