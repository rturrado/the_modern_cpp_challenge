#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies/samples.h"
#include "chapter_09_data_serialization/problem_074_using_xpath.h"
#include "chapter_09_data_serialization/xml/pugixml_wrapper.h"
#include "chapter_09_data_serialization/xml/movies.h"

#include <fmt/ostream.h>
#include <iostream>  // cout
#include <pugixml.hpp>

#undef NDEBUG
#include <cassert>


namespace tmcppc::problem_74 {
    void print_movies_released_after_year(std::ostream& os, const tmcppc::movies::xml::doc& doc, int year) {
        fmt::print(os, "Movies released after year: {}\n", year);

        pugi::xpath_variable_set vars;
        vars.add("year", pugi::xpath_type_number);
        vars.set("year", static_cast<double>(year));
        const pugi::xpath_query query{ "/movies/movie[@year > $year]", &vars };
        auto movies{ query.evaluate_node_set(doc.get_pugi_xml_root()) };

        for (auto&& movie : movies) {
            fmt::print(os, "\t{}: {}\n",
                tmcppc::pugixml::attribute_or_throw(movie.node(), "title").as_string(),
                tmcppc::pugixml::attribute_or_throw(movie.node(), "year").as_int());
        }
    }


    void print_last_actor_in_casting_list_for_every_movie(std::ostream& os, const tmcppc::movies::xml::doc& doc) {
        fmt::print(os, "Last actor in the casting list for every movie:\n");

        const pugi::xpath_query query{ "/movies/movie" };
        auto movies{ query.evaluate_node_set(doc.get_pugi_xml_root()) };

        for (auto&& movie : movies) {
            const pugi::xpath_query query{ "cast/role[last()]" };
            auto actor{ query.evaluate_node(movie) };

            fmt::print(os, "\t{}: {}\n",
                tmcppc::pugixml::attribute_or_throw(movie.node(), "title").as_string(),
                tmcppc::pugixml::attribute_or_throw(actor.node(), "star").as_string());
        }
    }
}  // namespace tmcppc::problem_74


void problem_74_main(std::ostream& os) {
    using namespace tmcppc::movies;
    using namespace tmcppc::problem_74;

    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_movies.xml" };

    try {
        fmt::print(os, "Writing XML out to: {}\n", temp_file_path.generic_string());
        xml::doc out_doc{ samples::catalog };
        out_doc.save_to(temp_file_path);

        fmt::print(os, "Reading XML in from: {}\n\n", temp_file_path.generic_string());
        xml::doc in_doc{};
        in_doc.load_from(temp_file_path);

        fmt::print(os, "Checking if serializing and deserializing the XML object created the same object... ");
        assert(in_doc == out_doc and "Error: serializing and deserializing the XML object created a different object");
        fmt::print(os, "OK\n\n");

        for (auto year : { 1992, 1996, 2000 }) {
            print_movies_released_after_year(os, in_doc, year);
        }
        fmt::print(os, "\n");

        print_last_actor_in_casting_list_for_every_movie(os, in_doc);
        fmt::print(os, "\n");
    } catch (const std::exception& err) {
        fmt::print(os, "Error: {}\n\n", err.what());
    }
}


// Selecting data from XML using XPath
//
// Consider an XML file with a list of movies as described for the previous problem.
// Write a program that can select and print the following:
//
//   - The title of all movies released after a given year.
//   - The name of the last actor in the casting list for each movie in the file.
void problem_74_main() {
    problem_74_main(std::cout);
}
