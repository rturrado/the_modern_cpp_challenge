#include "chapter_09_data_serialization/movies.h"

#include "rtc/pretty_print.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <fmt/format.h>
#include <sstream>  // ostringstream

using namespace rtc::pretty_print;
using namespace std::chrono_literals;
using namespace tmcppc::movies;


// Role
tmcppc::movies::role r{ "Tom Hanks", "Forrest Gump" };
auto r_output{ "Tom Hanks (Forrest Gump)" };
TEST(role, print) {
    std::ostringstream oss{};
    r.print(oss);
    EXPECT_EQ(oss.str(), r_output);
}
TEST(role, operator_insertion) {
    std::ostringstream oss{};
    oss << r;
    EXPECT_EQ(oss.str(), r_output);
}
TEST(role, fmt_print) {
    EXPECT_EQ(fmt::format("{}", r), r_output);
}


// Cast
tmcppc::movies::cast c{{
    { "Tom Hanks", "Forrest Gump" },
    { "Sally Field", "Jenny" }
}};
auto c_output{ fmt::format("Cast:\n{0}Tom Hanks (Forrest Gump)\n{0}Sally Field (Jenny)\n", default_indentation_value) };
TEST(cast, print_empty_cast) {
    std::ostringstream oss{};
    cast{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Cast:\n{}[]\n", default_indentation_value));
}
TEST(cast, print) {
    std::ostringstream oss{};
    c.print(oss);
    EXPECT_EQ(oss.str(), c_output);
}
TEST(cast, operator_insertion) {
    std::ostringstream oss{};
    oss << c;
    EXPECT_EQ(oss.str(), c_output);
}
TEST(cast, fmt_print) {
    EXPECT_EQ(fmt::format("{}", c), c_output);
}


// Director
tmcppc::movies::director d{ "Robert Zemeckis" };
auto d_output{ "Robert Zemeckis" };
TEST(director, print) {
    std::ostringstream oss{};
    d.print(oss);
    EXPECT_EQ(oss.str(), d_output);
}
TEST(director, operator_insertion) {
    std::ostringstream oss{};
    oss << d;
    EXPECT_EQ(oss.str(), d_output);
}
TEST(director, fmt_print) {
    EXPECT_EQ(fmt::format("{}", d), d_output);
}


// Directors
tmcppc::movies::directors ds{{
    { "Lana Wachowski" },
    { "Lilly Wachowski" }
}};
auto ds_output{ fmt::format("Directors:\n{0}Lana Wachowski\n{0}Lilly Wachowski\n", default_indentation_value) };
TEST(directors, print_empty_directors) {
    std::ostringstream oss{};
    directors{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Directors:\n{}[]\n", default_indentation_value));
}
TEST(directors, print) {
    std::ostringstream oss{};
    ds.print(oss);
    EXPECT_EQ(oss.str(), ds_output);
}
TEST(directors, operator_insertion) {
    std::ostringstream oss{};
    oss << ds;
    EXPECT_EQ(oss.str(), ds_output);
}
TEST(directors, fmt_print) {
    EXPECT_EQ(fmt::format("{}", ds), ds_output);
}


// Writer
tmcppc::movies::writer w{ "Winston Groom" };
auto w_output{ "Winston Groom" };
TEST(writer, print) {
    std::ostringstream oss{};
    w.print(oss);
    EXPECT_EQ(oss.str(), w_output);
}
TEST(writer, operator_insertion) {
    std::ostringstream oss{};
    oss << w;
    EXPECT_EQ(oss.str(), w_output);
}
TEST(writer, fmt_print) {
    EXPECT_EQ(fmt::format("{}", w), w_output);
}


// Writers
tmcppc::movies::writers ws{{
    { "Winston Groom" },
    { "Eric Roth" }
}};
auto ws_output{ fmt::format("Writers:\n{0}Winston Groom\n{0}Eric Roth\n", default_indentation_value) };
TEST(writers, print_empty_writers) {
    std::ostringstream oss{};
    writers{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Writers:\n{}[]\n", default_indentation_value));
}
TEST(writers, print) {
    std::ostringstream oss{};
    ws.print(oss);
    EXPECT_EQ(oss.str(), ws_output);
}
TEST(writers, operator_insertion) {
    std::ostringstream oss{};
    oss << ws;
    EXPECT_EQ(oss.str(), ws_output);
}
TEST(writers, fmt_print) {
    EXPECT_EQ(fmt::format("{}", ws), ws_output);
}


// Media file
tmcppc::movies::media_file mf_without_description{ 1, "./res/db/BladeRunner.jpg" };
tmcppc::movies::media_file mf{ 1, "./res/db/BladeRunner.jpg", "Front cover" };
auto mf_without_description_output{
    fmt::format(
        "Media file:\n"
        "{0}id: 1\n"
        "{0}path: './res/db/BladeRunner.jpg'\n"
        "{0}description: ''\n",
        default_indentation_value
    )
};
auto mf_output{
    fmt::format(
        "Media file:\n"
        "{0}id: 1\n"
        "{0}path: './res/db/BladeRunner.jpg'\n"
        "{0}description: 'Front cover'\n",
        default_indentation_value
    )
};
TEST(media_file, print_empty_description) {
    std::ostringstream oss{};
    mf_without_description.print(oss);
    EXPECT_EQ(oss.str(), mf_without_description_output);
}
TEST(media_file, print_description) {
    std::ostringstream oss{};
    mf.print(oss);
    EXPECT_EQ(oss.str(), mf_output);
}
TEST(media_file, operator_insertion) {
    std::ostringstream oss{};
    oss << mf;
    EXPECT_EQ(oss.str(), mf_output);
}
TEST(media_file, fmt_print) {
    EXPECT_EQ(fmt::format("{}", mf), mf_output);
}


// Media files
tmcppc::movies::media_files mfs{{
    { 1, "./res/db/BladeRunner.jpg", "Front cover" },
    { 2, "./res/db/BladeRunner.mp4", "Trailer" }
}};
auto mfs_output{
    fmt::format(
        "Media files:\n"
        "{0}Media file:\n"
        "{0}{0}id: 1\n"
        "{0}{0}path: './res/db/BladeRunner.jpg'\n"
        "{0}{0}description: 'Front cover'\n"
        "{0}Media file:\n"
        "{0}{0}id: 2\n"
        "{0}{0}path: './res/db/BladeRunner.mp4'\n"
        "{0}{0}description: 'Trailer'\n",
        default_indentation_value
    )
};
TEST(media_files, print_empty_media_files) {
    std::ostringstream oss{};
    media_files{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Media files:\n{}[]\n", default_indentation_value));
}
TEST(media_files, print) {
    std::ostringstream oss{};
    mfs.print(oss);
    EXPECT_EQ(oss.str(), mfs_output);
}
TEST(media_files, operator_insertion) {
    std::ostringstream oss{};
    oss << mfs;
    EXPECT_EQ(oss.str(), mfs_output);
}
TEST(media_files, fmt_print) {
    EXPECT_EQ(fmt::format("{}", mfs), mfs_output);
}


// Movie
tmcppc::movies::movie mv{
    .id = 1,
    .title = "Forrest Gump",
    .year = 1994y,
    .length = 202,
    .cast = cast{{
        { .star = "Tom Hanks", .name = "Forrest Gump" },
        { .star = "Sally Field", .name = "Mrs. Gump" }
    }},
    .directors = directors{{
        { .name = "Robert Zemeckis" }
    }},
    .writers = writers{{
        { .name = "Winston Groom" },
        { .name = "Eric Roth" }
    }}
};
auto mv_output{
    fmt::format(
        "Movie:\n"
        "{0}id: 1\n"
        "{0}title: Forrest Gump\n"
        "{0}year: 1994\n"
        "{0}length: 202\n"
        "{0}Cast:\n"
        "{0}{0}Tom Hanks (Forrest Gump)\n"
        "{0}{0}Sally Field (Mrs. Gump)\n"
        "{0}Directors:\n"
        "{0}{0}Robert Zemeckis\n"
        "{0}Writers:\n"
        "{0}{0}Winston Groom\n"
        "{0}{0}Eric Roth\n"
        "{0}Media files:\n"
        "{0}{0}[]\n",
        default_indentation_value
    )
};
TEST(movie, print) {
    std::ostringstream oss{};
    mv.print(oss);
    EXPECT_EQ(oss.str(), mv_output);
}
TEST(movie, operator_insertion) {
    std::ostringstream oss{};
    oss << mv;
    EXPECT_EQ(oss.str(), mv_output);
}
TEST(movie, fmt_print) {
    EXPECT_EQ(fmt::format("{}", mv), mv_output);
}


// Catalog
tmcppc::movies::catalog mvs{{
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
            { .star = "Sally Field", .name = "Mrs. Gump" }
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
auto mvs_output{
    fmt::format(
        "Catalog:\n"
        "{0}Movie:\n"
        "{0}{0}id: 1\n"
        "{0}{0}title: The Matrix\n"
        "{0}{0}year: 1999\n"
        "{0}{0}length: 196\n"
        "{0}{0}Cast:\n"
        "{0}{0}{0}Keanu Reeves (Neo)\n"
        "{0}{0}{0}Carrie-Anne Moss (Trinity)\n"
        "{0}{0}Directors:\n"
        "{0}{0}{0}Lana Wachowski\n"
        "{0}{0}{0}Lilly Wachowski\n"
        "{0}{0}Writers:\n"
        "{0}{0}{0}Lana Wachowski\n"
        "{0}{0}{0}Lilly Wachowski\n"
        "{0}{0}Media files:\n"
        "{0}{0}{0}[]\n"
        "{0}Movie:\n"
        "{0}{0}id: 2\n"
        "{0}{0}title: Forrest Gump\n"
        "{0}{0}year: 1994\n"
        "{0}{0}length: 202\n"
        "{0}{0}Cast:\n"
        "{0}{0}{0}Tom Hanks (Forrest Gump)\n"
        "{0}{0}{0}Sally Field (Mrs. Gump)\n"
        "{0}{0}Directors:\n"
        "{0}{0}{0}Robert Zemeckis\n"
        "{0}{0}Writers:\n"
        "{0}{0}{0}Winston Groom\n"
        "{0}{0}{0}Eric Roth\n"
        "{0}{0}Media files:\n"
        "{0}{0}{0}[]\n",
        default_indentation_value
    )
};
TEST(catalog, print) {
    std::ostringstream oss{};
    mvs.print(oss);
    EXPECT_EQ(oss.str(), mvs_output);
}
TEST(catalog, operator_insertion) {
    std::ostringstream oss{};
    oss << mvs;
    EXPECT_EQ(oss.str(), mvs_output);
}
TEST(catalog, fmt_print) {
    EXPECT_EQ(fmt::format("{}", mvs), mvs_output);
}
