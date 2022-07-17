#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies_samples.h"
#include "chapter_09_data_serialization/json/movies.h"

#include "nlohmann/json.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace std::chrono_literals;
using namespace tmcppc::movies;


// Role
TEST(json_role, DISABLED_to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, role_sample);
    role r{};
    from_json(j, r);
    EXPECT_EQ(role_sample, r);
}

// Cast
TEST(json_cast, DISABLED_to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, cast_sample);
    cast c{};
    from_json(j, c);
    EXPECT_EQ(cast_sample, c);
}

// Director
TEST(json_director, DISABLED_to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, director_sample);
    director d{};
    from_json(j, d);
    EXPECT_EQ(director_sample, d);
}

// Directors
TEST(json_directors, DISABLED_to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, directors_sample);
    directors ds{};
    from_json(j, ds);
    EXPECT_EQ(directors_sample, ds);
}

// Writer
TEST(json_writer, DISABLED_to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, writer_sample);
    writer w{};
    from_json(j, w);
    EXPECT_EQ(writer_sample, w);
}

// Writers
TEST(json_writers, DISABLED_to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, writers_sample);
    writers ws{};
    from_json(j, ws);
    EXPECT_EQ(writers_sample, ws);
}

// Movie
TEST(json_movie, DISABLED_to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, movie_sample);
    movie mv{};
    from_json(j, mv);
    EXPECT_EQ(movie_sample, mv);
}

// Catalog
TEST(json_catalog, DISABLED_to_json_and_from_json) {
    nlohmann::json j{};
    to_json(j, catalog_sample);
    catalog c{};
    from_json(j, c);
    EXPECT_EQ(catalog_sample, c);
}

// JSON document
TEST(json_doc, DISABLED_save_to_and_load_from) {
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "test_doc_save_to_and_load_from.json" };
    doc out_doc{ catalog_sample };
    out_doc.save_to(temp_file_path);
    doc in_doc{};
    in_doc.load_from(temp_file_path);
    EXPECT_EQ(out_doc, in_doc);
}
