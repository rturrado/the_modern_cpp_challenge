#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/pugixml_wrapper.h"
#include "chapter_09_data_serialization/xml_movies.h"

#include "pugixml.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std::chrono_literals;
using namespace tmcppc::movies;
using namespace tmcppc::movies::xml;
using namespace tmcppc::pugixml;


// Role
TEST(role, to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "role") };
    role r{ "Tom Hanks", "Forrest Gump" };
    to_xml(n, r);
	role rr{};
	from_xml(n, rr);
	EXPECT_EQ(r, rr);
}


// Cast
TEST(cast, to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "cast") };
    cast c{ {
        { "Tom Hanks", "Forrest Gump" },
        { "Robin Wright", "Jenny Curran" }
    }};
    to_xml(n, c);
    cast cc{};
    from_xml(n, cc);
    EXPECT_EQ(c, cc);
}


// Director
TEST(director, to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "director") };
    director d{ "Robert Zemeckis" };
    to_xml(n, d);
    director dd{};
    from_xml(n, dd);
    EXPECT_EQ(d, dd);
}


// Directors
TEST(directors, to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "directors") };
    directors ds{{
        { "Lana Wachowski" },
        { "Lilly Wachowski" }
    }};
    to_xml(n, ds);
    directors dds{};
    from_xml(n, dds);
    EXPECT_EQ(ds, dds);
}


// Writer
TEST(writer, to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "writer") };
    writer w{ "Robert Zemeckis" };
    to_xml(n, w);
    writer ww{};
    from_xml(n, ww);
    EXPECT_EQ(w, ww);
}


// Writers
TEST(writers, to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "writers") };
    writers ws{{
        { "Winston Groom" },
        { "Eric Roth" }
    }};
    to_xml(n, ws);
    writers wws{};
    from_xml(n, wws);
    EXPECT_EQ(ws, wws);
}


// Movie
TEST(movie, to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "movie") };
    movie mv{
        .id = 1,
        .title = "Forrest Gump",
        .year = 1994y,
        .length = 202,
        .cast = cast{{
            { .star = "Tom Hanks", .name = "Forrest Gump" },
            { .star = "Robin Wright", .name = "Jenny Curran" }
        }},
        .directors = directors{{
            { .name = "Robert Zemeckis" }
        }},
        .writers = writers{{
            { .name = "Winston Groom" },
            { .name = "Eric Roth" }
        }}
    };
    to_xml(n, mv);
    movie mvv{};
    from_xml(n, mvv);
    EXPECT_EQ(mv, mvv);
}


// Catalog
TEST(catalog, to_xml_and_from_xml) {
    pugi::xml_document doc{};
    auto n{ append_child_or_throw(doc, "catalog") };
    catalog c{{
        {
            .id = 1,
            .title = "The Matrix",
            .year = 1999y,
            .length = 196,
            .cast = tmcppc::movies::cast{{
                { .star = "Keanu Reeves", .name = "Neo" },
                { .star = "Carrie-Anne Moss", .name = "Trinity" },
            }},
            .directors = directors{{
                { .name = "Lana Wachowski" },
                { .name = "Lilly Wachowski" }
            }},
            .writers = writers{{
                { .name = "Lana Wachowski" },
                { .name = "Lilly Wachowski" }
            }}
        },
        {
            .id = 2,
            .title = "Forrest Gump",
            .year = 1994y,
            .length = 202,
            .cast = cast{{
                { .star = "Tom Hanks", .name = "Forrest Gump" },
                { .star = "Robin Wright", .name = "Jenny Curran" }
            }},
            .directors = directors{{
                { .name = "Robert Zemeckis" }
            }},
            .writers = writers{{
                { .name = "Winston Groom" },
                { .name = "Eric Roth" }
            }}
        }
    }};
    to_xml(n, c);
    catalog cc{};
    from_xml(n, cc);
    EXPECT_EQ(c, cc);
}
