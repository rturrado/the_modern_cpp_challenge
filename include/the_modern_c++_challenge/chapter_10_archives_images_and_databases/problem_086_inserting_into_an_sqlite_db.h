#pragma once

#include "chapter_09_data_serialization/movies.h"
#include "chapter_10_archives_images_and_databases/sqlite_movies.h"

#include <iosfwd>


namespace tmcppc::problem_86 {
    void add_new_movie(std::istream& is, std::ostream& os, tmcppc::movies::sqlite_mcpp::database& movies_db, tmcppc::movies::movie& movie);
    void add_new_movie_from_console(std::istream& is, std::ostream& os, tmcppc::movies::sqlite_mcpp::database& movies_db);
    void add_new_movie_from_file(std::istream& is, std::ostream& os, tmcppc::movies::sqlite_mcpp::database& movies_db);
    void add_new_movies(std::istream& is, std::ostream& os, tmcppc::movies::sqlite_mcpp::database& movies_db);
}  // namespace tmcppc::problem_86


void problem_86_main(std::istream& is, std::ostream& os);
void problem_86_main();
