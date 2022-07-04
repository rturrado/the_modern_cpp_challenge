#include "chapter_09_data_serialization/movies.h"
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
    role r{ "Tom Hanks", "Forrest Gump" };
    to_json(j, r);
    role rr{};
    from_json(j, rr);
    EXPECT_EQ(r, rr);
}


// Cast
TEST(cast, to_json_and_from_json) {
    nlohmann::json j{};
    cast c{{
        { "Tom Hanks", "Forrest Gump" },
        { "Robin Wright", "Jenny Curran" }
    }};
    to_json(j, c);
    cast cc{};
    from_json(j, cc);
    EXPECT_EQ(c, cc);
}


// Director
TEST(director, to_json_and_from_json) {
    nlohmann::json j{};
    director d{ "Robert Zemeckis" };
    to_json(j, d);
    director dd{};
    from_json(j, dd);
    EXPECT_EQ(d, dd);
}


// Directors
TEST(directors, to_json_and_from_json) {
    nlohmann::json j{};
    directors ds{{
        { "Lana Wachowski" },
        { "Lilly Wachowski" }
    }};
    to_json(j, ds);
    directors dds{};
    from_json(j, dds);
    EXPECT_EQ(ds, dds);
}


// Writer
TEST(writer, to_json_and_from_json) {
    nlohmann::json j{};
    writer w{ "Robert Zemeckis" };
    to_json(j, w);
    writer ww{};
    from_json(j, ww);
    EXPECT_EQ(w, ww);
}


// Writers
TEST(writers, to_json_and_from_json) {
    nlohmann::json j{};
    writers ws{{
        { "Winston Groom" },
        { "Eric Roth" }
    }};
    to_json(j, ws);
    writers wws{};
    from_json(j, wws);
    EXPECT_EQ(ws, wws);
}


// Movie
TEST(movie, to_json_and_from_json) {
    nlohmann::json j{};
    movie mv{
        .id = 1,
        .title = "Forrest Gump",
        .year = 1994y,
        .length = 202,
        .cast = cast{{
            { .star = "Tom Hanks", .name = "Forrest Gump" },
            { .star = "Robin Wrigth", .name = "Jenny Curran" }
        }},
        .directors = directors{{
            { .name = "Robert Zemeckis" }
        }},
        .writers = writers{{
            { .name = "Winston Groom" },
            { .name = "Eric Roth" }
        }}
    };
    to_json(j, mv);
    movie mvv{};
    from_json(j, mvv);
    EXPECT_EQ(mv, mvv);
}


// Catalog
TEST(catalog, to_json_and_from_json) {
    nlohmann::json j{};
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
    to_json(j, c);
    catalog cc{};
    from_json(j, cc);
    EXPECT_EQ(c, cc);
}
