#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies_samples.h"
#include "chapter_09_data_serialization/json_movies.h"

#include "nlohmann/json.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace std::chrono_literals;
using namespace tmcppc::movies;


// Role
TEST(role, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, role_sample);
    role r{};
    from_json(j, r);
    EXPECT_EQ(role_sample, r);
}


// Cast
TEST(cast, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, cast_sample);
    cast c{};
    from_json(j, c);
    EXPECT_EQ(cast_sample, c);
}


// Director
TEST(director, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, director_sample);
    director d{};
    from_json(j, d);
    EXPECT_EQ(director_sample, d);
}


// Directors
TEST(directors, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, directors_sample);
    directors ds{};
    from_json(j, ds);
    EXPECT_EQ(directors_sample, ds);
}


// Writer
TEST(writer, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, writer_sample);
    writer w{};
    from_json(j, w);
    EXPECT_EQ(writer_sample, w);
}


// Writers
TEST(writers, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, writers_sample);
    writers ws{};
    from_json(j, ws);
    EXPECT_EQ(writers_sample, ws);
}


// Movie
TEST(movie, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, movie_sample);
    movie mv{};
    from_json(j, mv);
    EXPECT_EQ(movie_sample, mv);
}


// Catalog
TEST(catalog, to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, catalog_sample);
    catalog c{};
    from_json(j, c);
    EXPECT_EQ(catalog_sample, c);
}


// JSON document
TEST(json_doc, save_to_and_load_from) {
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "test_doc_save_to_and_load_from.json" };
    doc out_doc{ catalog_sample };
    out_doc.save_to(temp_file_path);
    doc in_doc{};
    in_doc.load_from(temp_file_path);
    EXPECT_EQ(out_doc, in_doc);
}
