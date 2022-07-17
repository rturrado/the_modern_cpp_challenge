#include "chapter_10_archives_images_and_databases/command_line_movies.h"
#include "chapter_10_archives_images_and_databases/problem_087_handling_images_in_an_sqlite_db.h"
#include "chapter_10_archives_images_and_databases/sql/movies.h"

#include <exception>
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>

namespace fs = std::filesystem;


void problem_87_main(std::istream& is, std::ostream& os) {
    const auto db_file_path{ fs::temp_directory_path() / "movies.db" };

    try {
        {
            auto sqlite_db{ tmcppc::movies::sql::create_movies_database(db_file_path) };
            auto movies_db{ tmcppc::movies::sql::database{ sqlite_db } };

            tmcppc::movies::command_line::menu(is, os, movies_db);
        }

        fmt::print(os, "\n");

        tmcppc::movies::sql::remove_movies_database_file(is, os, db_file_path);
    } catch (const sqlite::sqlite_exception& ex) {
        fmt::print(os, "Error: code = {}, message = '{}', operation = '{}'\n",
            ex.get_code(), ex.what(), ex.get_sql());
    } catch (const std::exception& ex) {
        fmt::print(os, "Error: {}\n", ex.what());
    }

    fmt::print(os, "\n");
}


// Handling movie images in an SQLite database
//
// Modify the program written for the previous problem to support adding media files (such as images, but also videos) to a movie.
// These files must be stored in a separate table in the database and have a unique numerical identifier, the movie identifier,
// a name (typically the filename), an optional description, and the actual media content, stored as a blob.
// The following is a diagram with the structure of the table that must be added to the existing database:
//
//   media
//   --------------------------
//   (key) rowid        integer
//         movieid      integer
//         name         text
//         description  text
//         content      blob
//
// The program written for this problem must support several commands:
//   - Listing all movies that match a search criterion (notably the title).
//   - Listing information about all existing media files for a movie.
//   - Adding a new media file for a movie.
//   - Deleting an existing media file.
void problem_87_main() {
    problem_87_main(std::cin, std::cout);
}
