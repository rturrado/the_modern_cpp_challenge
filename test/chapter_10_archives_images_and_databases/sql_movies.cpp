#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies_samples.h"
#include "chapter_10_archives_images_and_databases/sql/movies.h"

#include "env.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>

using namespace std::chrono_literals;
using namespace tmcppc::movies;
using namespace tmcppc::movies::sql;
namespace fs = std::filesystem;


auto get_updated_catalog_sample() {
    auto ret{ catalog_sample };
    ret.movies[0].id = 1;
    ret.movies[1].id = 2;
    return ret;
}
auto get_updated_media_files_sample() {
    auto ret{ media_files_sample };
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    ret.media_files_[0].file_path = resource_folder_path / "db" / "poster.png";
    ret.media_files_[1].file_path = resource_folder_path / "db" / "city.jpg";
    return ret;
}
auto get_updated_media_file_sample() {
    auto ret{ media_file_sample };
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    ret.file_path = resource_folder_path / "db" / "poster.png";
    return ret;
}

auto get_empty_sqlite_db() {
    auto sqlite_db{ sqlite::database{ ":memory:" } };
    create_empty_movies_database(sqlite_db);
    return sqlite_db;
}
auto get_empty_db() {
    sqlite::database sqlite_db{ ":memory:" };
    create_empty_movies_database(sqlite_db);
    return database{ sqlite_db };
}
static auto get_ok_db() {
    sqlite::database sqlite_db{ ":memory:" };
    create_movies_database(sqlite_db);
    return database{ sqlite_db };
}


TEST(sql_cast, DISABLED_to_db_movie_does_not_exist) {
    auto sqlite_db{ get_empty_sqlite_db() };
    EXPECT_THROW(to_db(sqlite_db, 111, cast_sample), movie_id_not_found_error);
}
TEST(sql_cast, DISABLED_to_db_cast_and_one_of_the_roles_already_exists) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 2, "Forrest Gump", 1994y, 202 };
    to_db(sqlite_db, m);
    to_db(sqlite_db, 1, cast_sample);
    EXPECT_THROW(to_db(sqlite_db, 1, cast_sample), trying_to_insert_existing_role_error);
    cast c{};
    from_db(sqlite_db, 1, c);
    EXPECT_EQ(c, cast_sample);
}
TEST(sql_cast, DISABLED_to_db_and_from_db) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 2, "Forrest Gump", 1994y, 202 };
    to_db(sqlite_db, m);
    to_db(sqlite_db, 1, cast_sample);
    cast c{};
    from_db(sqlite_db, 1, c);
    EXPECT_EQ(c, cast_sample);
}

TEST(sql_writers, DISABLED_to_db_movie_does_not_exist) {
    auto sqlite_db{ get_empty_sqlite_db() };
    EXPECT_THROW(to_db(sqlite_db, 111, writers_sample), movie_id_not_found_error);
}
TEST(sql_writers, DISABLED_to_db_writers_and_one_of_the_writers_already_exists) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 2, "Forrest Gump", 1994y, 202 };
    to_db(sqlite_db, m);
    to_db(sqlite_db, 1, writers_sample);
    EXPECT_THROW(to_db(sqlite_db, 1, writers_sample), trying_to_insert_existing_writer_error);
    writers ws{};
    from_db(sqlite_db, 1, ws);
    EXPECT_EQ(ws, writers_sample);
}
TEST(sql_writers, DISABLED_to_db_and_from_db) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 2, "Forrest Gump", 1994y, 202 };
    to_db(sqlite_db, m);
    to_db(sqlite_db, 1, writers_sample);
    writers ws{};
    from_db(sqlite_db, 1, ws);
    EXPECT_EQ(ws, writers_sample);
}

TEST(sql_directors, DISABLED_to_db_movie_does_not_exist) {
    auto sqlite_db{ get_empty_sqlite_db() };
    EXPECT_THROW(to_db(sqlite_db, 111, directors_sample), movie_id_not_found_error);
}
TEST(sql_directors, DISABLED_to_db_directors_and_one_of_the_directors_already_exists) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 2, "Forrest Gump", 1994y, 202 };
    to_db(sqlite_db, m);
    to_db(sqlite_db, 1, directors_sample);
    EXPECT_THROW(to_db(sqlite_db, 1, directors_sample), trying_to_insert_existing_director_error);
    directors ds{};
    from_db(sqlite_db, 1, ds);
    EXPECT_EQ(ds, directors_sample);
}
TEST(sql_directors, DISABLED_to_db_and_from_db) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 2, "Forrest Gump", 1994y, 202 };
    to_db(sqlite_db, m);
    to_db(sqlite_db, 1, directors_sample);
    directors ds{};
    from_db(sqlite_db, 1, ds);
    EXPECT_EQ(ds, directors_sample);
}

TEST(sql_media_files, DISABLED_to_db_movie_does_not_exist) {
    auto sqlite_db{ get_empty_sqlite_db() };
    auto non_const_media_files_sample_copy{ media_files_sample };
    EXPECT_THROW(to_db(sqlite_db, 111, non_const_media_files_sample_copy), movie_id_not_found_error);
}
TEST(sql_media_files, DISABLED_to_db_media_files_and_one_of_the_media_files_already_exists) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 1, "Blade Runner", 1982y, 117 };
    to_db(sqlite_db, m);
    auto updated_media_files_sample{ get_updated_media_files_sample() };
    to_db(sqlite_db, 1, updated_media_files_sample);
    EXPECT_THROW(to_db(sqlite_db, 1, updated_media_files_sample), trying_to_insert_existing_media_file_error);
    media_files mfs{};
    from_db(sqlite_db, 1, mfs);
    EXPECT_EQ(mfs, updated_media_files_sample);
}
TEST(sql_media_files, DISABLED_to_db_and_from_db) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 1, "Blade Runner", 1982y, 117 };
    to_db(sqlite_db, m);
    auto updated_media_files_sample{ get_updated_media_files_sample() };
    to_db(sqlite_db, 1, updated_media_files_sample);
    media_files mfs{};
    from_db(sqlite_db, 1, mfs);
    EXPECT_EQ(mfs, updated_media_files_sample);
}

TEST(sql_catalog, DISABLED_to_db_and_from_db_movie_already_exists) {
    auto sqlite_db{ get_empty_sqlite_db() };
    catalog updated_catalog_sample{ get_updated_catalog_sample() };
    to_db(sqlite_db, updated_catalog_sample.movies[0]);
    EXPECT_THROW(to_db(sqlite_db, updated_catalog_sample.movies[0]), trying_to_insert_existing_movie_error);
    to_db(sqlite_db, updated_catalog_sample.movies[1]);
    catalog c{};
    from_db(sqlite_db, c);
    EXPECT_EQ(c, updated_catalog_sample);
}
TEST(sql_catalog, DISABLED_to_db_and_from_db) {
    auto sqlite_db{ get_empty_sqlite_db() };
    catalog updated_catalog_sample{ get_updated_catalog_sample() };
    to_db(sqlite_db, updated_catalog_sample.movies[0]);
    to_db(sqlite_db, updated_catalog_sample.movies[1]);
    catalog c{};
    from_db(sqlite_db, c);
    EXPECT_EQ(c, updated_catalog_sample);
}

TEST(database, DISABLED_constructor_file_does_not_exist) {
    EXPECT_THROW(database{ fs::path{} }, sqlite::sqlite_exception);
}
TEST(database, DISABLED_constructor_file_does_not_contain_an_sqlite_db) {
    sqlite::database db_file_path{ ":memory:" };
    EXPECT_THROW(database{ db_file_path }, sqlite::sqlite_exception);
}

TEST(database, DISABLED_get_movies_does_not_get_any_movie) {
    auto db{ get_ok_db() };
    auto ret{ db.get_movies(std::regex{ R"(.*scent.*)" }) };
    EXPECT_TRUE(ret.movies.empty());
}
TEST(database, DISABLED_get_movies_gets_one_movie) {
    auto db{ get_ok_db() };
    auto ret{ db.get_movies(std::regex{ R"(.*Forrest.*)" }) };
    EXPECT_EQ(ret.movies.size(), 1);
    EXPECT_EQ(ret.movies[0], movie_with_id_initialized_after_database_insertion_sample);
}
TEST(database, DISABLED_get_movies_gets_all_movies) {
    auto db{ get_ok_db() };
    auto ret{ db.get_movies(std::regex{ R"(.*)" }) };
    EXPECT_EQ(ret.movies.size(), 2);
    auto updated_catalog_sample{ catalog_sample };
    updated_catalog_sample.movies[0].id = 1;
    updated_catalog_sample.movies[1].id = 2;
    EXPECT_EQ(ret, updated_catalog_sample);
}

TEST(database, DISABLED_get_media_files_does_not_find_movie_id) {
    auto db{ get_ok_db() };
    EXPECT_THROW((void) db.get_media_files(12345), movie_id_not_found_error);
}
TEST(database, DISABLED_get_media_files_finds_movie_id_but_movie_does_not_have_media_files) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 1, "Blade Runner", 1982y, 117 };
    to_db(sqlite_db, m);
    database db{ sqlite_db };
    EXPECT_TRUE(db.get_media_files(1).media_files_.empty());
}
TEST(database, DISABLED_get_media_files_finds_movie_id_and_gets_media_files) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 1, "Blade Runner", 1982y, 117 };
    to_db(sqlite_db, m);
    auto updated_media_files_sample{ get_updated_media_files_sample() };
    to_db(sqlite_db, 1, updated_media_files_sample);
    database db{ sqlite_db };
    EXPECT_EQ(db.get_media_files(1), updated_media_files_sample);
}

TEST(database, DISABLED_insert_movie_that_does_not_exist) {
    auto sqlite_db{ get_empty_sqlite_db() };
    database db{ sqlite_db };
    movie m{ 2, "Forrest Gump", 1994y, 202 };
    db.insert_movie(m);
    EXPECT_EQ(db.catalog_.movies.size(), 1);
}
TEST(database, DISABLED_insert_movie_that_exists_already) {
    auto sqlite_db{ get_empty_sqlite_db() };
    database db{ sqlite_db };
    movie m{ 2, "Forrest Gump", 1994y, 202 };
    db.insert_movie(m);    
    EXPECT_THROW(db.insert_movie(m), trying_to_insert_existing_movie_error);
    EXPECT_EQ(db.catalog_.movies.size(), 1);
}

TEST(database, DISABLED_insert_media_file_that_does_not_exist) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 1, "Blade Runner", 1982y, 117 };
    to_db(sqlite_db, m);
    database db{ sqlite_db };
    media_file mf{ get_updated_media_file_sample() };
    media_files mfs{ { mf } };
    db.insert_media_file(1, mf);
    EXPECT_EQ(db.get_media_files(1), mfs);
}
TEST(database, DISABLED_insert_media_file_that_exists_already) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 1, "Blade Runner", 1982y, 117 };
    to_db(sqlite_db, m);
    database db{ sqlite_db };
    auto mf{ get_updated_media_file_sample() };
    media_files mfs{ { mf } };
    db.insert_media_file(1, mf);
    EXPECT_THROW(db.insert_media_file(1, mf), trying_to_insert_existing_media_file_error);
    EXPECT_EQ(db.get_media_files(1), mfs);
}

TEST(database, DISABLED_delete_media_file_does_not_find_media_id) {
    auto db{ get_empty_db() };
    EXPECT_THROW(db.delete_media_file(1991), media_file_id_not_found_error);
}
TEST(database, DISABLED_delete_media_file_finds_media_id) {
    auto sqlite_db{ get_empty_sqlite_db() };
    movie m{ 1, "Blade Runner", 1982y, 117 };
    media_files mfs{ { get_updated_media_file_sample() } };
    to_db(sqlite_db, m);
    to_db(sqlite_db, 1, mfs);
    database db{ sqlite_db };
    db.delete_media_file(1);
    EXPECT_TRUE(db.get_media_files(1).media_files_.empty());
}
