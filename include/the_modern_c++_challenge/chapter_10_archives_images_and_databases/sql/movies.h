#pragma once

#include "chapter_09_data_serialization/movies.h"

#include "rtc/console.h"  // read_char
#include "rtc/filesystem.h"

#ifndef __GNUC__
    #pragma warning(disable:4065)
    #pragma warning(disable:4267)
    #pragma warning(disable:4996)
#endif
#define MODERN_SQLITE_STD_OPTIONAL_SUPPORT
#include "sqlite_modern_cpp.h"
#ifndef __GNUC__
    #pragma warning(default:4065)
    #pragma warning(default:4267)
    #pragma warning(default:4996)
#endif

#include <algorithm>  // copy_if
#include <chrono>
#include <cstdint>  // int64_t
#include <filesystem>
#include "fmt/format.h"
#include "fmt/ostream.h"
#include <fstream>  // ofstream
#include <ios>  // ios_base
#include <istream>
#include <iterator>  // back_inserter
#include <optional>
#include <ostream>
#include <ranges>
#include <regex>
#include <stdexcept>  // runtime_error
#include <sstream>  // ostringstream
#include <string>
#include <vector>


namespace tmcppc::movies::sql {
    namespace fs = std::filesystem;

    struct error : public std::runtime_error {
        explicit error(const std::string& message) : std::runtime_error{ message } {}
    };

    struct movie_id_not_found_error : public error {
        explicit movie_id_not_found_error(std::int64_t movie_id)
            : error{ message_ + std::to_string(movie_id) }
        {}
    private:
        static inline std::string message_{ "movie id not found: " };
    };

    struct media_file_id_not_found_error : public error {
        explicit media_file_id_not_found_error(std::int64_t media_file_id)
            : error{ message_ + std::to_string(media_file_id) }
        {}
    private:
        static inline std::string message_{ "media file id not found: " };
    };

    struct trying_to_insert_existing_role_error : public error {
        trying_to_insert_existing_role_error(std::int64_t movie_id, const role_t& r)
            : error{ message_ + fmt::format("movie id = {}, star = {}, role = {}",
                movie_id, r.star, r.name) }
        {}
    private:
        static inline std::string message_{ "trying to insert existing role: " };
    };

    struct trying_to_insert_existing_writer_error : public error {
        trying_to_insert_existing_writer_error(std::int64_t movie_id, const writer_t& w)
            : error{ message_ + fmt::format("movie id = {}, name = {}", movie_id, w.name) }
        {}
    private:
        static inline std::string message_{ "trying to insert existing writer: " };
    };

    struct trying_to_insert_existing_director_error : public error {
        trying_to_insert_existing_director_error(std::int64_t movie_id, const director_t& d)
            : error{ message_ + fmt::format("movie id = {}, name = {}", movie_id, d.name) }
        {}
    private:
        static inline std::string message_{ "trying to insert existing director: " };
    };

    struct trying_to_insert_existing_movie_error : public error {
        explicit trying_to_insert_existing_movie_error(const movie_t& m)
            : error{ message_ + fmt::format("title = {}, year = {}, length = {}", m.title, int(m.year), m.length) }
        {}
    private:
        static inline std::string message_{ "trying to insert existing movie_t: " };
    };

    struct trying_to_insert_existing_media_file_error : public error {
        trying_to_insert_existing_media_file_error(std::int64_t movie_id, const media_file_t& mf)
            : error{ message_ + fmt::format("movie id = {}, file_path = {}, description = '{}'",
                movie_id, mf.file_path.generic_string(), mf.description.value_or("")) }
        {}
    private:
        static inline std::string message_{ "trying to insert existing media file: " };
    };

    inline void create_tables(sqlite::database& db) {
        db << "create table if not exists Movies ("
            "title text not null, year integer not null, length integer not null);";
        db << "create table if not exists Persons ("
            "name text not null);";
        db << "create table if not exists Directors ("
            "movie_id integer not null, person_id integer not null);";
        db << "create table if not exists Writers ("
            "movie_id integer not null, person_id integer not null);";
        db << "create table if not exists Cast ("
            "movie_id integer not null, person_id integer not null, role text not null);";
        db << "create table if not exists Media ("
            "movie_id integer not null, name text not null, description text, content blob not null);";
    }
    inline void fill_movies_table(sqlite::database& db) {
        db << "insert into Movies (title, year, length) values (?,?,?);" << "The Matrix" << 1999 << 196;
        db << "insert into Movies (title, year, length) values (?,?,?);" << "Forrest Gump" << 1994 << 202;
    }
    inline void fill_persons_table(sqlite::database& db) {
        db << "insert into Persons (name) values (?);" << "Keanu Reeves";
        db << "insert into Persons (name) values (?);" << "Laurence Fishburne";
        db << "insert into Persons (name) values (?);" << "Carrie-Anne Moss";
        db << "insert into Persons (name) values (?);" << "Hugo Weaving";
        db << "insert into Persons (name) values (?);" << "Lana Wachowski";
        db << "insert into Persons (name) values (?);" << "Lilly Wachowski";
        db << "insert into Persons (name) values (?);" << "Tom Hanks";
        db << "insert into Persons (name) values (?);" << "Sally Field";
        db << "insert into Persons (name) values (?);" << "Robin Wright";
        db << "insert into Persons (name) values (?);" << "Mykelti Williamson";
        db << "insert into Persons (name) values (?);" << "Robert Zemeckis";
        db << "insert into Persons (name) values (?);" << "Winston Groom";
        db << "insert into Persons (name) values (?);" << "Eric Roth";
    }
    inline void fill_directors_table(sqlite::database& db) {
        db << "insert into Directors (movie_id, person_id) values (?,?);" << 1 << 5;
        db << "insert into Directors (movie_id, person_id) values (?,?);" << 1 << 6;
        db << "insert into Directors (movie_id, person_id) values (?,?);" << 2 << 11;
    }
    inline void fill_writers_table(sqlite::database& db) {
        db << "insert into Writers (movie_id, person_id) values (?,?);" << 1 << 5;
        db << "insert into Writers (movie_id, person_id) values (?,?);" << 1 << 6;
        db << "insert into Writers (movie_id, person_id) values (?,?);" << 2 << 12;
        db << "insert into Writers (movie_id, person_id) values (?,?);" << 2 << 13;
    }
    inline void fill_cast_table(sqlite::database& db) {
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 1 << "Neo";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 2 << "Morpheus";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 3 << "Trinity";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 4 << "Agent Smith";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 7 << "Forrest Gump";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 8 << "Mrs. Gump";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 9 << "Jenny Curran";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 10 << "Bubba Blue";
    }

    inline void create_empty_movies_database(sqlite::database& db) {
        db << "begin;";
        create_tables(db);
        db << "commit;";
    }

    inline void create_movies_database(sqlite::database& db) {
        db << "begin;";
        create_tables(db);
        fill_movies_table(db);
        fill_persons_table(db);
        fill_directors_table(db);
        fill_writers_table(db);
        fill_cast_table(db);
        db << "commit;";
    }

    [[nodiscard]] inline auto create_movies_database(const fs::path& db_file_path) {
        if (fs::exists(db_file_path)) {
            return sqlite::database{ db_file_path.string() };
        }
        sqlite::database db{ db_file_path.string() };
        create_movies_database(db);
        return db;
    }

    [[nodiscard]] inline auto remove_movies_database_file(std::istream& is, std::ostream& os, const fs::path& db_file_path) {
        auto c{
            rtc::console::read_char(is, os,
                fmt::format("Are you sure you want to remove '{}'? [y/n] ", db_file_path.generic_string()),
                std::vector<char>{'n', 'N', 'y', 'Y'}
        )};
        if (c == 'y' or c == 'Y') {
            fs::remove(db_file_path);
        }
    }

    [[nodiscard]] inline bool exists_director(sqlite::database& db, std::int64_t movie_id, const director_t& director) {
        bool ret{ false };
        db << "select 1 from Persons P join Directors D on P.rowid == D.person_id "
            "where D.movie_id = (?) and P.name = (?);"
            << movie_id << director.name
            >> [&ret]() { ret = true; };
        return ret;
    }

    [[nodiscard]] inline bool exists_media_file(sqlite::database& db, std::int64_t media_file_id) {
        bool ret{ false };
        db << "select 1 from Media where rowid = (?);" << media_file_id
            >> [&ret]() { ret = true; };
        return ret;
    }

    [[nodiscard]] inline bool exists_media_file(sqlite::database& db, std::int64_t movie_id, const std::filesystem::path& file_path,
        const std::optional<std::string>& description) {

        bool ret{ false };
        db << "select 1 from Media M "
            "where M.movie_id = (?) and M.name = (?) and (M.description = (?) or M.description is null) and M.content = (?);"
            << movie_id << file_path.generic_string() << description
            << rtc::filesystem::get_binary_file_content<char>(file_path)
            >> [&ret]() { ret = true; };
        return ret;
    }

    [[nodiscard]] inline bool exists_movie(sqlite::database& db, std::int64_t movie_id) {
        bool ret{ false };
        db << "select 1 from Movies "
            "where rowid = (?);"
            << movie_id
            >> [&ret]() { ret = true; };
        return ret;
    }

    [[nodiscard]] inline bool exists_movie(sqlite::database& db, const std::string& title, std::chrono::year year, size_t length) {
        bool ret{ false };
        db << "select 1 from Movies M "
            "where M.title = (?) and M.year = (?) and M.length = (?);"
            << title << static_cast<int>(year) << length
            >> [&ret]() { ret = true; };
        return ret;
    }

    [[nodiscard]] inline bool exists_role(sqlite::database& db, std::int64_t movie_id, const role_t& role) {
        bool ret{ false };
        db << "select 1 from Persons P join Cast C on P.rowid == C.person_id "
            "where C.movie_id = (?) and P.name = (?) and C.role = (?);"
            << movie_id << role.star << role.name
            >> [&ret]() { ret = true; };
        return ret;
    }

    [[nodiscard]] inline bool exists_person(sqlite::database& db, const std::string& name) {
        bool ret{ false };
        db << "select 1 from Persons "
            "where name = (?);"
            << name
            >> [&ret]() { ret = true; };
        return ret;
    }

    [[nodiscard]] inline bool exists_writer(sqlite::database& db, std::int64_t movie_id, const writer_t& writer) {
        bool ret{ false };
        db << "select 1 from Persons P join Writers W on P.rowid == W.person_id "
            "where W.movie_id = (?) and P.name = (?);"
            << movie_id << writer.name
            >> [&ret]() { ret = true; };
        return ret;
    }

    [[nodiscard]] inline std::int64_t get_person_id_from_person_name(sqlite::database& db, const std::string& name) {
        std::int64_t ret{};
        db << "select rowid from Persons "
            "where name = (?);"
            << name
            >> [&ret](std::int64_t rowid) { ret = rowid; };
        return ret;
    }

    [[nodiscard]] inline std::int64_t get_movie_id_from_media_file_id(sqlite::database& db, std::int64_t media_file_id) {
        std::int64_t ret{};
        db << "select movie_id from Media "
            "where rowid = (?);"
            << media_file_id
            >> [&ret](std::int64_t movie_id) { ret = movie_id; };
        return ret;
    }

    // Role
    inline void to_db(sqlite::database& db, std::int64_t movie_id, const role_t& role) {
        if (not exists_movie(db, movie_id)) {
            throw movie_id_not_found_error{ movie_id };
        }
        if (exists_role(db, movie_id, role)) {
            throw trying_to_insert_existing_role_error{ movie_id, role };
        }
        std::int64_t person_id;
        if (exists_person(db, role.star)) {
            person_id = get_person_id_from_person_name(db, role.star);
        } else {
            db << "insert into Persons (name) values (?);" << role.star;
            person_id = db.last_insert_rowid();
        }
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);"
            << movie_id
            << person_id
            << role.name;
    }

    // Cast
    inline void from_db(sqlite::database& db, std::int64_t movie_id, cast_t& cast) {
        db << "select P.name as name, C.role as role "
            "from Persons P join Cast C on P.rowid = C.person_id "
            "where C.movie_id = (?);"
            << movie_id
            >> [&cast](const std::string& name, const std::string& role) {
            cast.data.emplace_back(name, role);
        };
    }
    inline void to_db(sqlite::database& db, std::int64_t movie_id, const cast_t& cast) {
        for (const auto& role : cast.data) {
            to_db(db, movie_id, role);
        }
    }

    // Writer
    inline void to_db(sqlite::database& db, std::int64_t movie_id, const writer_t& writer) {
        if (not exists_movie(db, movie_id)) {
            throw movie_id_not_found_error{ movie_id };
        }
        if (exists_writer(db, movie_id, writer)) {
            throw trying_to_insert_existing_writer_error{ movie_id, writer };
        }
        std::int64_t person_id;
        if (exists_person(db, writer.name)) {
            person_id = get_person_id_from_person_name(db, writer.name);
        } else {
            db << "insert into Persons (name) values (?);" << writer.name;
            person_id = db.last_insert_rowid();
        }
        db << "insert into Writers (movie_id, person_id) values (?,?);"
            << movie_id
            << person_id;
    }

    // Writers
    inline void from_db(sqlite::database& db, std::int64_t movie_id, writers_t& writers) {
        db << "select name from Persons P join Writers W on P.rowid = W.person_id "
            "where W.movie_id = (?);"
            << movie_id
            >> [&writers](const std::string& name) {
            writers.data.emplace_back(name);
        };
    }
    inline void to_db(sqlite::database& db, std::int64_t movie_id, const writers_t& writers) {
        for (const auto& writer : writers.data) {
            to_db(db, movie_id, writer);
        }
    }

    // Director
    inline void to_db(sqlite::database& db, std::int64_t movie_id, const director_t& director) {
        if (not exists_movie(db, movie_id)) {
            throw movie_id_not_found_error{ movie_id };
        }
        if (exists_director(db, movie_id, director)) {
            throw trying_to_insert_existing_director_error{ movie_id, director };
        }
        std::int64_t person_id;
        if (exists_person(db, director.name)) {
            person_id = get_person_id_from_person_name(db, director.name);
        } else {
            db << "insert into Persons (name) values (?);"
                << director.name;
            person_id = db.last_insert_rowid();
        }
        db << "insert into Directors (movie_id, person_id) values (?,?);"
            << movie_id
            << person_id;
    }

    // Directors
    inline void from_db(sqlite::database& db, std::int64_t movie_id, directors_t& directors) {
        db << "select name from Persons P join Directors D on P.rowid = D.person_id "
            "where D.movie_id = (?);"
            << movie_id
            >> [&directors](const std::string& name) {
            directors.data.emplace_back(name);
        };
    }
    inline void to_db(sqlite::database& db, std::int64_t movie_id, const directors_t& directors) {
        for (const auto& director : directors.data) {
            to_db(db, movie_id, director);
        }
    }

    // Media file
    //
    // to_db updates media_file.id
    inline void to_db(sqlite::database& db, std::int64_t movie_id, media_file_t& media_file) {
        if (not exists_movie(db, movie_id)) {
            throw movie_id_not_found_error{ movie_id };
        }
        if (exists_media_file(db, movie_id, media_file.file_path, media_file.description)) {
            throw trying_to_insert_existing_media_file_error{ movie_id, media_file };
        }
        db << "insert into Media (movie_id,name,description,content) values (?,?,?,?);"
            << movie_id
            << media_file.file_path.generic_string()
            << media_file.description
            << rtc::filesystem::get_binary_file_content<char>(media_file.file_path);

        media_file.id = db.last_insert_rowid();
    }

    // Media files
    inline void from_db(sqlite::database& db, std::int64_t movie_id, media_files_t& media_files) {
        db << "select rowid,name,description from Media "
            "where movie_id = (?);"
            << movie_id
            >> [&media_files](int rowid, const std::string& name, const std::optional<std::string>& description) {
            media_files.data.emplace_back(rowid, name, description);
        };
    }
    inline void to_db(sqlite::database& db, std::int64_t movie_id, media_files_t& media_files) {
        for (auto& media_file : media_files.data) {
            to_db(db, movie_id, media_file);
        }
    }

    // Movie
    //
    // to_db updates movie.id
    inline void to_db(sqlite::database& db, movie_t& movie) {
        if (exists_movie(db, movie.title, movie.year, movie.length)) {
            throw trying_to_insert_existing_movie_error{ movie };
        }
        db << "insert into Movies (title,year,length) values (?,?,?);"
            << movie.title << static_cast<int>(movie.year) << movie.length;

        movie.id = db.last_insert_rowid();

        to_db(db, movie.id, movie.cast);
        to_db(db, movie.id, movie.directors);
        to_db(db, movie.id, movie.writers);
        to_db(db, movie.id, movie.media_files);
    }

    // Catalog
    inline void from_db(sqlite::database& db, catalog_t& catalog) {
        db << "select rowid,title,year,length from Movies;"
            >> [&catalog](int rowid, const std::string& title, int year, int length) {
            catalog.movies.emplace_back(rowid, title, std::chrono::year{ year }, length);
        };
        for (auto& movie : catalog.movies) {
            from_db(db, movie.id, movie.cast);
            from_db(db, movie.id, movie.directors);
            from_db(db, movie.id, movie.writers);
            from_db(db, movie.id, movie.media_files);
        }
    }

    // Database
    struct database {
        catalog_t catalog_{};

        explicit database(const fs::path& db_file_path)
            : sqlite_db_{ db_file_path.string() } {
            from_db(sqlite_db_, catalog_);
        }
        explicit database(sqlite::database& sqlite_db)
            : sqlite_db_{sqlite_db} {
            from_db(sqlite_db_, catalog_);
        }

    private:
        template <typename Database>
        [[nodiscard]] friend auto find_movie_impl(Database& db, std::int64_t movie_id) {
            return
                std::ranges::find_if(
                    db.catalog_.movies,
                    [&movie_id](std::int64_t id) { return id == movie_id; },
                    &movie_t::id);
        }
        [[nodiscard]] auto find_movie(std::int64_t movie_id) { return find_movie_impl(*this, movie_id); }
        [[nodiscard]] auto find_movie(std::int64_t movie_id) const { return find_movie_impl(*this, movie_id); }

        [[nodiscard]] static auto find_media_file(const movie_t& movie, std::int64_t media_file_id) {
            return
                std::ranges::find_if(
                    movie.media_files.data,
                    [&media_file_id](std::int64_t id) { return id == media_file_id; },
                    &media_file_t::id);
        }

    public:
        [[nodiscard]] auto get_movies(const std::regex& pattern) const noexcept {
            tmcppc::movies::catalog_t ret{};
            std::ranges::copy_if(
                catalog_.movies,
                std::back_inserter(ret.movies),
                [&pattern](const auto& title) { return std::regex_match(title.c_str(), pattern); },
                &movie_t::title);
            return ret;
        }

        [[nodiscard]] auto get_media_files(std::int64_t movie_id) const {
            auto movie_it{ find_movie(movie_id) };

            if (movie_it == std::end(catalog_.movies)) {
                throw movie_id_not_found_error{ movie_id };
            }

            return movie_it->media_files;
        }

        // to_db updates movie.id
        void insert_movie(movie_t& movie) {
            try {
                sqlite_db_ << "begin;";
                to_db(sqlite_db_, movie);
                sqlite_db_ << "commit;";

                catalog_.movies.push_back(movie);
            } catch (const sqlite::sqlite_exception&) {
                sqlite_db_ << "rollback;";

                throw;
            }
        }

        // to_db updates media_file_t.id
        void insert_media_file(std::int64_t movie_id, media_file_t& media_file) {
            auto movie_it{ find_movie(movie_id) };

            if (movie_it == std::end(catalog_.movies)) {
                throw movie_id_not_found_error{ movie_id };
            }

            try {
                sqlite_db_ << "begin;";
                to_db(sqlite_db_, movie_id, media_file);
                sqlite_db_ << "commit;";

                movie_it->media_files.data.push_back(media_file);
            } catch (const sqlite::sqlite_exception&) {
                sqlite_db_ << "rollback;";

                throw;
            }
        }

        void delete_media_file(std::int64_t media_file_id) {
            if (not exists_media_file(sqlite_db_, media_file_id)) {
                throw media_file_id_not_found_error{ media_file_id };
            }
            try {
                auto movie_id{ get_movie_id_from_media_file_id(sqlite_db_, media_file_id) };
                auto movie_it{ find_movie(movie_id) };
                auto media_file_it{ find_media_file(*movie_it, media_file_id) };

                sqlite_db_ << "begin;";
                sqlite_db_ << "delete from Media where rowid = (?);" << media_file_id;
                sqlite_db_ << "commit;";

                movie_it->media_files.data.erase(media_file_it);
            } catch (const sqlite::sqlite_exception&) {
                sqlite_db_ << "rollback;";

                throw;
            }
        }

    private:
        sqlite::database sqlite_db_;
    };
    inline std::ostream& operator<<(std::ostream& os, const database& db) { return os << db.catalog_; }
}  // namespace tmcppc::movies::sql


template <>
struct fmt::formatter<tmcppc::movies::sql::database> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::sql::database& database, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", database.catalog_);
    }
};
