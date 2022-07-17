#pragma once

#include "chapter_09_data_serialization/movies.h"
#include "chapter_10_archives_images_and_databases/sql/movies.h"

#include <iosfwd>


namespace tmcppc::problem_86 {
    [[nodiscard]] std::string remove_movie_id_line(const std::string& movie_str);
    void add_new_movie(std::istream& is, std::ostream& os, tmcppc::movies::sql::database& movies_db, const tmcppc::movies::movie& movie);
    void add_new_movie_from_console(std::istream& is, std::ostream& os, tmcppc::movies::sql::database& movies_db);
    void add_new_movie_from_file(std::istream& is, std::ostream& os, tmcppc::movies::sql::database& movies_db);
    void add_new_movies(std::istream& is, std::ostream& os, tmcppc::movies::sql::database& movies_db);
}  // namespace tmcppc::problem_86


void problem_86_main(std::istream& is, std::ostream& os);
void problem_86_main();
