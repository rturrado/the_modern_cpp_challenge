#include "chapter_10_archives_images_and_databases.h"
#include "chapter_10_archives_images_and_databases/sqlite_movies.h"

#include <filesystem>
#include <format>
#include <iostream>  // cout


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
void problem_85_main()
{
    const auto db_file_path{ std::filesystem::current_path() / "res" / "db" / "movies.db" };

    try
    {
        {
            auto sqlite_db{ tmcppc::movies::sqlite_mcpp::create_movies_database(db_file_path) };
            auto movies_db{ tmcppc::movies::sqlite_mcpp::database{ sqlite_db } };

            std::cout << movies_db;
        }

        std::cout << "\n";

        tmcppc::movies::sqlite_mcpp::remove_movies_database_file(db_file_path);
    }
    catch (const sqlite::sqlite_exception& ex)
    {
        std::cout << std::format("Error: code = {}, message = '{}', operation '{}'\n",
            ex.get_code(), ex.what(), ex.get_sql());
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }

    std::cout << "\n";
}
