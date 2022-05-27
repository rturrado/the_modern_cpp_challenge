#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/pdf_movies.h"
#include "chapter_09_data_serialization/problem_077_printing_a_list_of_movies_to_a_pdf.h"

#include <chrono>
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>


void problem_77_main(std::ostream& os) {
    using namespace std::chrono_literals;

    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_movies.pdf" };

    try {
        fmt::print(os, "Writing PDF out to: {}\n\n", temp_file_path.generic_string());
        tmcppc::movies::pdf::doc out_doc{
            tmcppc::movies::catalog{{
                { 1, "The Matrix", 1999y, 136 },
                { 2, "Forrest Gump", 1994y, 142 },
                { 3, "The Truman Show", 1998y, 103 },
                { 4, "The Pursuit of Happyness", 2006y, 117 },
                { 5, "Fight Club", 1999y, 139 },
                { 6, "Inglourious Basterds", 2009y, 153 },
                { 7, "The Dark Knight Rises", 2012y, 164 },
                { 8, "The Dark Knight", 2008y, 152 },
                { 9, "Pulp Fiction", 1994y, 154 },
                { 10, "Inception", 2010y, 148 },
                { 11, "The Shawshank Redemption", 1994y, 142 },
                { 12, "The Silence of the Lambs", 1991y, 118 },
                { 13, "Philadelphia", 1993y, 125 },
                { 14, "One Flew Over the Cuckoo's Nest", 1975y, 80 },
                { 15, "Memento", 2000y, 113 },
                { 16, "Trainspotting", 1996y, 94 },
                { 17, "Fargo", 1998y, 98 },
                { 18, "Reservoir Dogs", 1992y, 99 },
                { 19, "The Departed", 2006y, 151 },
                { 20, "Se7en", 1995y, 127 },
                { 21, "American History X", 1998y, 119 },
                { 22, "Silver Linings Playbook", 2012y, 122 },
                { 23, "2001: A Space Odyssey", 1968y, 149 },
                { 24, "Monty Python and the Holy Grail", 1975y, 91 },
                { 25, "Life of Brian", 1979y, 94 },
                { 26, "Children of Men", 2006y, 109 },
                { 27, "Sin City", 2005y, 124 },
                { 28, "L.A. Confidential", 1997y, 138 },
                { 29, "Shutter Island", 2010y, 138 },
            }}
        };
        out_doc.save_as_table(temp_file_path);
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
