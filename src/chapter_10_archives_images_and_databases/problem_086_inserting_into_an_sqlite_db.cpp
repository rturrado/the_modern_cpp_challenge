#include "chapter_09_data_serialization/movies.h"
#include "chapter_10_archives_images_and_databases.h"
#include "chapter_10_archives_images_and_databases/console_movies.h"
#include "chapter_10_archives_images_and_databases/file_movies.h"
#include "chapter_10_archives_images_and_databases/sqlite_movies.h"

#include "rtc/console.h"

#include <filesystem>
#include <format>
#include <fstream>  // ifstream
#include <iostream>  // cout
#include <sstream>  // ostringstream

namespace fs = std::filesystem;


// insert_movie updates movie.id
void add_new_movie(tmcppc::movies::sqlite_mcpp::database& movies_db, tmcppc::movies::movie& movie)
{
    std::ostringstream oss{};
    oss << movie << "\nAre you sure you want to add this movie to the movies database? [y/n] ";
    auto c{ read_char(oss.str(), { 'n', 'N', 'y', 'Y' }) };
    if (c == 'y' or c == 'Y')
    {
        movies_db.insert_movie(movie);
    }
}

void add_new_movie_from_console(tmcppc::movies::sqlite_mcpp::database& movies_db)
{
    std::cout << "Please enter the movie data (ID will be later overwritten with DB's Movies.rowid)\n";
    tmcppc::movies::movie movie{};
    tmcppc::movies::console::from_console(movie);
    add_new_movie(movies_db, movie);
}

void add_new_movie_from_file(tmcppc::movies::sqlite_mcpp::database& movies_db)
{
    const fs::path new_movies_file_path{ fs::current_path() / "res" / "db" / "NewMovies.txt" };
    std::cout << "Adding movies from " << new_movies_file_path.generic_string() << "\n";
    std::ifstream ifs{ new_movies_file_path };
    try
    {
        std::string line{};
        std::getline(ifs, line);
        int number_of_movies{ std::stoi(line) };
        while (number_of_movies--)
        {
            tmcppc::movies::movie movie{};
            tmcppc::movies::file::from_file(ifs, movie);
            add_new_movie(movies_db, movie);
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }
}

void add_new_movies(tmcppc::movies::sqlite_mcpp::database& movies_db)
{
    for (;;)
    {
        auto input_option{ read_char(
            "Choose method for adding a new movie (1 - Console,  2 - File, q - Quit): ",
            { '1', '2', 'q'}
        )};
        switch (input_option)
        {
        case '1': add_new_movie_from_console(movies_db); break;
        case '2': add_new_movie_from_file(movies_db); break;
        case 'q': return;
        default: break;
        }
    }
    std::cout << "\n";
}


// Inserting movies into an SQLite database transactionally
//
// Extend the program written for the previous problem so that it can add new movies to the database.
// The movies could be read from the console, or alternatively from a text file.
// The insertion of movie data into several tables in the database must be performed transactionally.
void problem_86_main()
{
    const auto db_file_path{ fs::current_path() / "res" / "db" / "movies.db" };

    try
    {
        {
            auto sqlite_db{ tmcppc::movies::sqlite_mcpp::create_movies_database(db_file_path) };
            auto movies_db{ tmcppc::movies::sqlite_mcpp::database{ sqlite_db } };

            add_new_movies(movies_db);

            std::cout << movies_db;
        }

        std::cout << "\n";

        tmcppc::movies::sqlite_mcpp::remove_movies_database_file(db_file_path);
    }
    catch (const sqlite::sqlite_exception& ex)
    {
        std::cout << std::format("Error: code = {}, message = '{}', operation = '{}'\n",
            ex.get_code(), ex.what(), ex.get_sql());
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }

    std::cout << "\n";
}
