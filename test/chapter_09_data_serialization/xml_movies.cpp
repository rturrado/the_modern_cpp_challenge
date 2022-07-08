#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies_samples.h"
#include "chapter_09_data_serialization/xml/pugixml_wrapper.h"
#include "chapter_09_data_serialization/xml/movies.h"

#include "pugixml.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std::chrono_literals;
using namespace tmcppc::movies;
using namespace tmcppc::movies::xml;
using namespace tmcppc::pugixml;


// Role
TEST(role, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "role") };
    to_xml(n, role_sample);
	role r{};
	from_xml(n, r);
	EXPECT_EQ(role_sample, r);
}

// Cast
TEST(cast, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "cast") };
    to_xml(n, cast_sample);
    cast c{};
    from_xml(n, c);
    EXPECT_EQ(cast_sample, c);
}

// Director
TEST(director, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "director") };
    to_xml(n, director_sample);
    director d{};
    from_xml(n, d);
    EXPECT_EQ(director_sample, d);
}

// Directors
TEST(directors, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "directors") };
    to_xml(n, directors_sample);
    directors ds{};
    from_xml(n, ds);
    EXPECT_EQ(directors_sample, ds);
}

// Writer
TEST(writer, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "writer") };
    to_xml(n, writer_sample);
    writer w{};
    from_xml(n, w);
    EXPECT_EQ(writer_sample, w);
}

// Writers
TEST(writers, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "writers") };
    to_xml(n, writers_sample);
    writers ws{};
    from_xml(n, ws);
    EXPECT_EQ(writers_sample, ws);
}

// Movie
TEST(movie, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "movie") };
    to_xml(n, movie_sample);
    movie mv{};
    from_xml(n, mv);
    EXPECT_EQ(movie_sample, mv);
}

// Catalog
TEST(catalog, DISABLED_to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "catalog") };
    to_xml(n, catalog_sample);
    catalog mvs{};
    from_xml(n, mvs);
    EXPECT_EQ(catalog_sample, mvs);
}

// XML document
TEST(xml_doc, DISABLED_save_to_and_load_from) {
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "test_doc_save_to_and_load_from.xml" };
    doc out_doc{ catalog_sample };
    out_doc.save_to(temp_file_path);
    doc in_doc{};
    in_doc.load_from(temp_file_path);
    EXPECT_EQ(out_doc, in_doc);
}
