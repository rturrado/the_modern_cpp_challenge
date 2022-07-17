#include "chapter_10_archives_images_and_databases/problem_085_reading_from_an_sqlite_db.h"
#include "chapter_10_archives_images_and_databases/sql/movies.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>

namespace fs = std::filesystem;


void problem_85_main(std::istream& is, std::ostream& os) {
    const auto db_file_path{ fs::temp_directory_path() / "movies.db" };

    try {
        {
            auto sqlite_db{ tmcppc::movies::sql::create_movies_database(db_file_path) };
            auto movies_db{ tmcppc::movies::sql::database{ sqlite_db } };

            fmt::print(os, "{}", movies_db);
        }

        fmt::print(os, "\n");

        tmcppc::movies::sql::remove_movies_database_file(is, os, db_file_path);
    } catch (const sqlite::sqlite_exception& ex) {
        fmt::print(os, "Error: code = {}, message = '{}', operation '{}'\n",
            ex.get_code(), ex.what(), ex.get_sql());
    } catch (const std::exception& ex) {
        fmt::print(os, "Error: {}\n", ex.what());
    }

    fmt::print(os, "\n");
}


// Reading movies from an SQLite database
//
// Write a program that reads movies from an SQLite database and displays them on the console.
// Each movie must have a numerical identifier, a title, release year, length in minutes, list of directors, list of writers,
// and a cast that includes both the actor and the character names.
// The following is a diagram of the database that should be used for this purpose:
//
//   movies                         persons
//   ---------------------          ---------------------
//   (key) rowid   integer          (key) rowid   integer
//         title   text                   name    text
//         year    integer
//         length  integer
//
//   directors                        writers                          casting
//   -----------------------          -----------------------          -----------------------
//   (key) rowid     integer          (key) rowid     integer          (key) rowid     integer
//         movieid   integer                movieid   integer                movieid   integer
//         personid  integer                personid  integer                personid  integer
//                                                                           role      text
void problem_85_main() {
    problem_85_main(std::cin, std::cout);
}
