#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies/samples.h"
#include "chapter_09_data_serialization/pdf/movies_doc.h"
#include "chapter_09_data_serialization/pdf/text_list_layouter.h"
#include "chapter_09_data_serialization/problem_077_printing_a_list_of_movies_to_a_pdf.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <memory>  // make_unique
#include <ostream>


void problem_77_main(std::ostream& os) {
    using namespace tmcppc::movies;
    using namespace tmcppc::pdf;

    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_movies.pdf" };

    try {
        fmt::print(os, "Writing PDF out to: {}\n\n", temp_file_path.generic_string());
        movies_doc out_doc{ samples::catalog_of_50_movies };
        out_doc.save_to(temp_file_path, std::make_unique<text_list_layouter>(25));
    } catch (const std::exception& err) {
        fmt::print(os, "Error: {}\n\n", err.what());
    }
}


// Printing a list of movies to a PDF
//
// Write a program that can print to a PDF file a list of movies in a tabular form, with the following requirements:
//
//   - There must be a heading to the list with the content 'List of movies'.
//     This must appear only on the first page of the document.
//   - For each movie, it should display the title, the release year, and the length.
//   - The title, followed by the release year in parentheses, must be left-aligned.
//   - The length, in hours and minutes (for example, 2:12), must be right-aligned.
//   - There must be a line above and below the movie listing on each page.
//
// Here is an example of such a PDF output:
//
//    List of movies
//    ----------------------------------------
//    The Matrix (1999)                   2:16
//    Forrest Gump (1994)                 2:22
//    The Truman Show (1998)              1:43
//    The Pursuit of Happyness (2006)     1:57
//    Fight Club (1999)                   2:19
//    ----------------------------------------
void problem_77_main() {
    problem_77_main(std::cout);
}
