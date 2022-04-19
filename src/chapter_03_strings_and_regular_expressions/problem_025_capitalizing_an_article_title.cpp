#include "chapter_03_strings_and_regular_expressions/problem_025_capitalizing_an_article_title.h"

#include <algorithm>  // for_each
#include <cctype>  // isalpha, tolower, toupper
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <string>


std::string capitalize(const std::string& s) {
    std::string ret{s};
    std::for_each(begin(ret), end(ret), [parsing_word = false](char& c) mutable {
        if (parsing_word) {
            // End of word. Update parsing word flag
            if (not std::isalpha(c)) {
                parsing_word = false;
            }
            // Else, just another word char
            else {
                c = std::tolower(c);
            }
        }
        else {
            // First word char. Capitalize it and update parsing word flag
            if (std::isalpha(c)) {
                c = std::toupper(c);
                parsing_word = true;
            }
            // Else, just another non word char
        }
    });
    return ret;
}


void problem_25_main(std::ostream& os) {
    std::string s1{ "the c++ challenger" };
    std::string s2{ "THIS IS an ExamplE, should wORk!" };
    fmt::print(os, "Capitalizing word \"{}\": \"{}\"\n", s1, capitalize(s1));
    fmt::print(os, "Capitalizing word \"{}\": \"{}\"\n\n", s2, capitalize(s2));
}


// Capitalizing an article title
// 
// Write a function that transforms an input text into a capitalized version,
// where every word starts with an uppercase letter and has all the other letters in lowercase.
// For instance, the text "the c++ challenger" should be transformed to "The C++ Challenger".
void problem_25_main() {
    problem_25_main(std::cout);
}
