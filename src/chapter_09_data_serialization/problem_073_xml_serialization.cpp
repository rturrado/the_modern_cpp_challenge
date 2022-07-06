#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies_samples.h"
#include "chapter_09_data_serialization/problem_073_xml_serialization.h"
#include "chapter_09_data_serialization/xml_movies.h"

#include <cassert>  // assert
#include <chrono>
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>


void problem_73_main(std::ostream& os) {
    using namespace tmcppc::movies;

    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_movies.xml" };

    try {
        fmt::print(os, "Writing XML out to: {}\n", temp_file_path.generic_string());
        xml::doc out_doc{ catalog_sample };
        out_doc.save_to(temp_file_path);

        fmt::print(os, "Reading XML in from: {}\n\n", temp_file_path.generic_string());
        xml::doc in_doc{};
        in_doc.load_from(temp_file_path);

        fmt::print(os, "Checking if serializing and deserializing the XML object created the same object... ");
        assert(in_doc == out_doc and "Error: serializing and deserializing the XML object created a different object");
        fmt::print(os, "OK\n\n");
    } catch (const std::exception& err) {
        fmt::print(os, "Error: {}\n\n", err.what());
    }
}


// Serializing and deserializing data to/from XML
//
// Write a program that can serialize a list of movies to an XML file, and deserialize an XML file with a list of movies.
// Each movie has a numerical identifier, title, release year, length in minutes, a list of directors, a list of writers,
// and a list of casting roles with actor name and character name.
// Such an XML may look like the following:
//
//   <?xml version="1.0">
//   <movies>
//     <movie id="9871" title="Forrest Gump" year="1994" length="202">
//       <cast>
//         <role star="Tom Hanks" name="Forrest Gump" />
//         <role star="Sally Field" name="Mrs. Gump" />
//         <role star="Robin Wright" name="Jenny Curran" />
//         <role star="Mykelti Williamson" name="Bubba Blue" />
//       </cast>
//       <directors>
//         <director name="Robert Zemeckis" />
//       </directors>
//       <writers>
//         <writer name="Winston Groom" />
//         <writer name="Eric Roth" />
//       </writers>
//     </movie>
//     <!-- more movie elements -->
//   </movies>
void problem_73_main() {
    problem_73_main(std::cout);
}
