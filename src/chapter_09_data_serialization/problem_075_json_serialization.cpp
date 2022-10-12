#include "chapter_09_data_serialization/json/movies.h"
#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies/samples.h"
#include "chapter_09_data_serialization/problem_075_json_serialization.h"

#include <fmt/ostream.h>
#include <ostream>


// Serializing data to JSON
//
// Write a program that can serialize a list of movies, as defined for the previous problems, to a JSON file.
// Each movie has a numerical identifier, title, release year, length in minutes, a list of directors, a list of writers,
// and a list of casting roles with actor name and character name.
// The following is an example of the expected JSON format:
//
//    {
//        "movies" : [{
//            "id": 9871,
//            "title": "Forrest Gump",
//            "year": 1994,
//            "length": 202,
//            "cast": [{
//                "star": "Tom Hanks",
//                "name": "Forrest Gump",
//            },
//            {
//                "star": "Sally Field",
//                "name": "Mrs. Gump",
//            },
//            {
//                "star": "Robin Wright",
//                "name": "Jenny Curran",
//            },
//            {
//                "star": "Mykelti Williamson",
//                "name": "Bubba Blue",
//            }
//            }],
//            "directors": ["Robert Zemeckis"],
//            "writers": ["Winston Groom", "Eric Roth"],
//        }]
//    }
void problem_75_main(std::ostream& os) {
    using namespace tmcppc::movies;

    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_movies.json" };

    try {
        fmt::print(os, "Writing JSON out to: {}\n", temp_file_path.generic_string());
        doc out_doc{ samples::catalog };
        out_doc.save_to(temp_file_path);

        fmt::print(os, "Reading JSON in from: {}\n\n", temp_file_path.generic_string());
        doc in_doc{};
        in_doc.load_from(temp_file_path);

        fmt::print(os, "Checking if serializing and deserializing the JSON object created the same object... ");
        assert(in_doc == out_doc and "Error: serializing and deserializing the JSON object created a different object");
        fmt::print(os, "OK\n\n");
    } catch (const std::exception& err) {
        fmt::print(os, "Error: {}\n\n", err.what());
    }
}
