#include "chapter_03_strings_and_regular_expressions/problem_030_extracting_url_parts.h"
#include "chapter_03_strings_and_regular_expressions/url.h"

#include <exception>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>


void problem_30_main(std::ostream& os) {
    for (const auto& s : { "http://user:pass@example.com:992/animal/bird?species=seagull#wings",
                           "http://example.com/animal/bird#wings",
                           "This is not a valid URL!" }) {
        try {
            tmcppc::url u{ s };
            fmt::print(os, "Parsing URL \"{}\":\n{}\n", s, u);
        }
        catch (const std::exception& err) {
            fmt::print(os, "Error: {}\n", err.what());
        }
    }

    fmt::print(os, "\n");
}


// Extracting URL parts
//
// Write a function that, given a string that represents a URL, parses and extracts the parts of the URL
// (protocol, domain, port, path, query, and fragment)
void problem_30_main() {
    problem_30_main(std::cout);
}
