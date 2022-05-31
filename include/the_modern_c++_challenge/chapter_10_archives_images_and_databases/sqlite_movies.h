#pragma once

#include "chapter_09_data_serialization/movies.h"

#include "rtc/console.h"  // read_char
#include "rtc/filesystem.h"

#pragma warning(disable:4065)
#pragma warning(disable:4267)
#pragma warning(disable:4996)
#define MODERN_SQLITE_STD_OPTIONAL_SUPPORT
#include "sqlite_modern_cpp.h"
#pragma warning(default:4065)
#pragma warning(default:4267)
#pragma warning(default:4996)

#include <algorithm>  // copy_if
#include <chrono>
#include <filesystem>
#include <fmt/ostream.h>
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


namespace tmcppc::movies::sqlite_mcpp {
    namespace fs = std::filesystem;

    struct movie_id_not_found_error : public std::runtime_error {
        movie_id_not_found_error(size_t movie_id)
            : std::runtime_error{ message_ + std::to_string(movie_id) }
        {}
    private:
        static inline std::string message_{ "movie id not found: " };
    };

    struct media_file_id_not_found_error : public std::runtime_error {
        media_file_id_not_found_error(size_t media_file_id)
            : std::runtime_error{ message_ + std::to_string(media_file_id) }
        {}
    private:
        static inline std::string message_{ "media file id not found: " };
    };

    [[nodiscard]] inline auto create_movies_database(const fs::path& db_file_path) {
        if (fs::exists(db_file_path)) {
            return sqlite::database{ db_file_path.string() };
        }

        sqlite::database db{ db_file_path.string() };

        db << "begin;";

        db << "create table if not exists Movies ("
            "title text not null,"
            "year integer not null,"
            "length integer not null"
            ");";
        db << "create table if not exists Persons ("
            "name text not null"
            ");";
        db << "create table if not exists Directors ("
            "movie_id integer not null,"
            "person_id integer not null"
            ");";
        db << "create table if not exists Writers ("
            "movie_id integer not null,"
            "person_id integer not null"
            ");";
        db << "create table if not exists Cast ("
            "movie_id integer not null,"
            "person_id integer not null,"
            "role text not null"
            ");";
        db << "create table if not exists Media ("
            "movie_id integer not null,"
            "name text not null,"
            "description text,"
            "content blob not null"
            ");";

        db << "insert into Movies (title, year, length) values (?,?,?);" << "The Matrix" << 1999 << 196;
        db << "insert into Movies (title, year, length) values (?,?,?);" << "Forrest Gump" << 1994 << 202;

        db << "insert into Persons (name) values (?);" << "Keanu Reeves";
        db << "insert into Persons (name) values (?);" << "Laurence Fishburne";
        db << "insert into Persons (name) values (?);" << "Carrie - Anne Moss";
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

        db << "insert into directors (movie_id, person_id) values (?,?);" << 1 << 5;
        db << "insert into directors (movie_id, person_id) values (?,?);" << 1 << 6;
        db << "insert into directors (movie_id, person_id) values (?,?);" << 2 << 11;

        db << "insert into Writers (movie_id, person_id) values (?,?);" << 1 << 5;
        db << "insert into Writers (movie_id, person_id) values (?,?);" << 1 << 6;
        db << "insert into Writers (movie_id, person_id) values (?,?);" << 2 << 12;
        db << "insert into Writers (movie_id, person_id) values (?,?);" << 2 << 13;

        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 1 << "Neo";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 2 << "Morpheus";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 3 << "Trinity";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 1 << 4 << "Agent Smith";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 7 << "Forrest Gump";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 8 << "Mrs.Gump";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 9 << "Jenny Curran";
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);" << 2 << 10 << "Bubba Blue";

        db << "commit;";

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

    [[nodiscard]] inline bool exists_person(sqlite::database& db, const std::string& name) {
        bool ret{ false };
        db << "select 1 from Persons where name = (?);" << name
            >> [&ret]() { ret = true; };
        return ret;
    }

    [[nodiscard]] inline int get_person_id_from_person_name(sqlite::database& db, const std::string& name) {
        int ret{};
        db << "select rowid from Persons where name = (?);" << name
            >> [&ret](int rowid) { ret = rowid; };
        return ret;
    }

    [[nodiscard]] inline bool exists_media_file(sqlite::database& db, size_t media_file_id) {
        bool ret{ false };
        db << "select 1 from Media where rowid = (?);" << media_file_id
            >> [&ret]() { ret = true; };
        return ret;
    }

    [[nodiscard]] inline int get_movie_id_from_media_file_id(sqlite::database& db, size_t media_file_id) {
        int ret{};
        db << "select movie_id from Media where rowid = (?);" << media_file_id
            >> [&ret](int movie_id) { ret = movie_id; };
        return ret;
    }

    // Role
    inline void to_db(sqlite::database& db, size_t movie_id, const role& role) {
        size_t person_id{};
        if (exists_person(db, role.star)) {
            person_id = get_person_id_from_person_name(db, role.star);
        } else {
            db << "insert into Persons (name) values (?);" << role.star;
            person_id = static_cast<int>(db.last_insert_rowid());
        }
        db << "insert into Cast (movie_id, person_id, role) values (?,?,?);"
            << static_cast<int>(movie_id)
            << person_id
            << role.name;
    }

    // Cast
    inline void from_db(sqlite::database& db, size_t movie_id, cast& cast) {
        db << "select P.name as name, C.role as role from Persons P join Cast C on P.rowid = C.person_id where C.movie_id = (?);"
            << movie_id
            >> [&cast](std::string name, std::string role) {
            cast.cast_.emplace_back(name, role);
        };
    }
    inline void to_db(sqlite::database& db, size_t movie_id, const cast& cast) {
        for (auto& role : cast.cast_) {
            to_db(db, movie_id, role);
        }
    }

    // Writer
    inline void to_db(sqlite::database& db, size_t movie_id, const writer& writer) {
        int person_id{};
        if (exists_person(db, writer.name)) {
            person_id = get_person_id_from_person_name(db, writer.name);
        } else {
            db << "insert into Persons (name) values (?);" << writer.name;
            person_id = static_cast<int>(db.last_insert_rowid());
        }
        db << "insert into Writers (movie_id, person_id) values (?,?);"
            << static_cast<int>(movie_id)
            << person_id;
    }

    // Writers
    inline void from_db(sqlite::database& db, size_t movie_id, writers& writers) {
        db << "select name from Persons P join Writers W on P.rowid = W.person_id where W.movie_id = (?);" << movie_id
            >> [&writers](std::string name) {
            writers.writers_.emplace_back(name);
        };
    }
    inline void to_db(sqlite::database& db, size_t movie_id, const writers& writers) {
        for (auto& writer : writers.writers_) {
            to_db(db, movie_id, writer);
        }
    }

    // Director
    inline void to_db(sqlite::database& db, size_t movie_id, const director& director) {
        int person_id{};
        if (exists_person(db, director.name)) {
            person_id = get_person_id_from_person_name(db, director.name);
        } else {
            db << "insert into Persons (name) values (?);"
                << director.name;
            person_id = static_cast<int>(db.last_insert_rowid());
        }
        db << "insert into Directors (movie_id, person_id) values (?,?);"
            << movie_id
            << person_id;
    }

    // Directors
    inline void from_db(sqlite::database& db, size_t movie_id, directors& directors) {
        db << "select name from Persons P join Directors D on P.rowid = D.person_id where D.movie_id = (?);" << movie_id
            >> [&directors](std::string name) {
            directors.directors_.emplace_back(name);
        };
    }
    inline void to_db(sqlite::database& db, size_t movie_id, const directors& directors) {
        for (auto& director : directors.directors_) {
            to_db(db, movie_id, director);
        }
    }

    // Media file
    //
    // to_db updates media_file.id
    inline void to_db(sqlite::database& db, size_t movie_id, media_file& media_file) {
        db << "insert into Media (movie_id,name,description,content) values (?,?,?,?);"
            << static_cast<int>(movie_id)
            << media_file.file_path.generic_string()
            << media_file.description
            << rtc::filesystem::get_binary_file_content<char>(media_file.file_path);

        media_file.id = db.last_insert_rowid();
    }

    // Media files
    inline void from_db(sqlite::database& db, size_t movie_id, media_files& media_files) {
        db << "select rowid,name,description from Media where movie_id = (?);" << movie_id
            >> [&media_files](int rowid, std::string name, std::optional<std::string> description) {
            media_files.media_files_.emplace_back(rowid, name, description);
        };
    }
    // to_db updates movie.id
    inline void to_db(sqlite::database& db, size_t movie_id, media_files& media_files) {
        for (auto& media_file : media_files.media_files_) {
            to_db(db, movie_id, media_file);
        }
    }

    // Movie
    //
    // to_db updates movie.id
    inline void to_db(sqlite::database& db, movie& movie) {
        db << "insert into Movies (title,year,length) values (?,?,?);"
            << movie.title
            << static_cast<int>(movie.year)
            << movie.length;

        movie.id = db.last_insert_rowid();

        to_db(db, static_cast<size_t>(movie.id), movie.cast);
        to_db(db, static_cast<size_t>(movie.id), movie.directors);
        to_db(db, static_cast<size_t>(movie.id), movie.writers);
        to_db(db, static_cast<size_t>(movie.id), movie.media_files);
    }

    // Catalog
    inline void from_db(sqlite::database& db, catalog& catalog) {
        db << "select rowid,title,year,length from Movies;"
            >> [&db, &catalog](int rowid, std::string title, int year, int length) {
            catalog.movies.emplace_back(rowid, title, std::chrono::year{ year }, length);
        };
        for (auto& movie : catalog.movies) {
            from_db(db, movie.id, movie.cast);
            from_db(db, movie.id, movie.directors);
            from_db(db, movie.id, movie.writers);
            from_db(db, movie.id, movie.media_files);
        }
    }

    // database
    struct database {
        catalog catalog_{};

        database(const fs::path& db_file_path)
            : sqlite_db_{ db_file_path.string() } {
            from_db(sqlite_db_, catalog_);
        }
        database(sqlite::database& sqlite_db)
            : sqlite_db_{sqlite_db} {
            from_db(sqlite_db_, catalog_);
        }

    private:
        template <typename Database>
        [[nodiscard]] friend auto find_movie_impl(Database& db, size_t movie_id) {
            return
                std::ranges::find_if(
                    db.catalog_.movies,
                    [&movie_id](size_t id) { return id == movie_id; },
                    &movie::id);
        }
        [[nodiscard]] auto find_movie(size_t movie_id) { return find_movie_impl(*this, movie_id); }
        [[nodiscard]] auto find_movie(size_t movie_id) const { return find_movie_impl(*this, movie_id); }

        [[nodiscard]] auto find_media_file(const movie& movie, size_t media_file_id) const {
            return
                std::ranges::find_if(
                    movie.media_files.media_files_,
                    [&media_file_id](size_t id) { return id == media_file_id; },
                    &media_file::id);
        }

    public:
        [[nodiscard]] auto get_movies(const std::regex& pattern) const noexcept {
            tmcppc::movies::catalog ret{};
            std::ranges::copy_if(
                catalog_.movies,
                std::back_inserter(ret.movies),
                [&pattern](const auto& title) { return std::regex_match(title.c_str(), pattern); },
                &movie::title);
            return ret;
        }

        [[nodiscard]] auto get_media_files(size_t movie_id) const {
            auto movie_it{ find_movie(movie_id) };

            if (movie_it == std::end(catalog_.movies)) {
                throw movie_id_not_found_error{ movie_id };
            }

            return movie_it->media_files;
        }

        // to_db updates movie.id
        void insert_movie(movie& movie) {
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

        // to_db updates media_file.id
        void insert_media_file(size_t movie_id, media_file& media_file) {
            auto movie_it{ find_movie(movie_id) };

            if (movie_it == std::end(catalog_.movies)) {
                throw movie_id_not_found_error{ movie_id };
            }

            try {
                sqlite_db_ << "begin;";
                to_db(sqlite_db_, movie_id, media_file);
                sqlite_db_ << "commit;";

                movie_it->media_files.media_files_.push_back(media_file);
            } catch (const sqlite::sqlite_exception&) {
                sqlite_db_ << "rollback;";

                throw;
            }
        }

        void delete_media_file(size_t media_file_id) {
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

                movie_it->media_files.media_files_.erase(media_file_it);
            } catch (const sqlite::sqlite_exception&) {
                sqlite_db_ << "rollback;";

                throw;
            }
        }

    private:
        sqlite::database sqlite_db_;
    };
    inline std::ostream& operator<<(std::ostream& os, const database& db) { return os << db.catalog_; }
}  // namespace tmcppc::movies::sqlite_mcpp


template <>
struct fmt::formatter<tmcppc::movies::sqlite_mcpp::database> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::movies::sqlite_mcpp::database& database, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", database.catalog_);
    }
};
