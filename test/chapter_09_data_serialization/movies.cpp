#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies/samples.h"

#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream

using namespace rtc::pretty_print;
using namespace tmcppc::movies;


// Role
TEST(role, print) {
    std::ostringstream oss{};
    samples::role.print(oss);
    EXPECT_EQ(oss.str(), samples::role_output);
}
TEST(role, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::role;
    EXPECT_EQ(oss.str(), samples::role_output);
}
TEST(role, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::role), samples::role_output);
}

// Cast
TEST(cast, print_empty_cast) {
    std::ostringstream oss{};
    cast_t{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Cast: []"));
}
TEST(cast, print) {
    std::ostringstream oss{};
    samples::cast.print(oss);
    EXPECT_EQ(oss.str(), samples::get_cast_2_output());
}
TEST(cast, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::cast;
    EXPECT_EQ(oss.str(), samples::get_cast_2_output());
}
TEST(cast, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::cast), samples::get_cast_2_output());
}

// Director
TEST(director, print) {
    std::ostringstream oss{};
    samples::director.print(oss);
    EXPECT_EQ(oss.str(), samples::director_output);
}
TEST(director, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::director;
    EXPECT_EQ(oss.str(), samples::director_output);
}
TEST(director, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::director), samples::director_output);
}

// Directors
TEST(directors, print_empty_directors) {
    std::ostringstream oss{};
    directors_t{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Directors: []"));
}
TEST(directors, print) {
    std::ostringstream oss{};
    samples::directors.print(oss);
    EXPECT_EQ(oss.str(), samples::get_directors_2_output());
}
TEST(directors, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::directors;
    EXPECT_EQ(oss.str(), samples::get_directors_2_output());
}
TEST(directors, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::directors), samples::get_directors_2_output());
}

// Writer
TEST(writer, print) {
    std::ostringstream oss{};
    samples::writer.print(oss);
    EXPECT_EQ(oss.str(), samples::writer_output);
}
TEST(writer, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::writer;
    EXPECT_EQ(oss.str(), samples::writer_output);
}
TEST(writer, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::writer), samples::writer_output);
}

// Writers
TEST(writers, print_empty_writers) {
    std::ostringstream oss{};
    writers_t{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Writers: []"));
}
TEST(writers, print) {
    std::ostringstream oss{};
    samples::writers.print(oss);
    EXPECT_EQ(oss.str(), samples::get_writers_2_output());
}
TEST(writers, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::writers;
    EXPECT_EQ(oss.str(), samples::get_writers_2_output());
}
TEST(writers, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::writers), samples::get_writers_2_output());
}

// Media file
TEST(media_file, print_empty_description) {
    std::ostringstream oss{};
    samples::media_file_without_description.print(oss);
    EXPECT_EQ(oss.str(), samples::get_media_file_without_description_output());
}
TEST(media_file, print_description) {
    std::ostringstream oss{};
    samples::media_file.print(oss);
    EXPECT_EQ(oss.str(), samples::get_media_file_1_output());
}
TEST(media_file, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::media_file;
    EXPECT_EQ(oss.str(), samples::get_media_file_1_output());
}
TEST(media_file, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::media_file), samples::get_media_file_1_output());
}

// Media files
TEST(media_files, print_empty_media_files) {
    std::ostringstream oss{};
    media_files_t{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Media files: []"));
}
TEST(media_files, print) {
    std::ostringstream oss{};
    samples::media_files.print(oss);
    EXPECT_EQ(oss.str(), samples::get_media_files_output());
}
TEST(media_files, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::media_files;
    EXPECT_EQ(oss.str(), samples::get_media_files_output());
}
TEST(media_files, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::media_files), samples::get_media_files_output());
}

// Movie
TEST(movie, print) {
    std::ostringstream oss{};
    samples::movie.print(oss);
    EXPECT_EQ(oss.str(), samples::get_movie_2_output());
}
TEST(movie, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::movie;
    EXPECT_EQ(oss.str(), samples::get_movie_2_output());
}
TEST(movie, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::movie), samples::get_movie_2_output());
}

// Catalog
TEST(catalog, print) {
    std::ostringstream oss{};
    samples::catalog.print(oss);
    EXPECT_EQ(oss.str(), samples::get_catalog_output());
}
TEST(catalog, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::catalog;
    EXPECT_EQ(oss.str(), samples::get_catalog_output());
}
TEST(catalog, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::catalog), samples::get_catalog_output());
}
