#include "chapter_04_streams_and_filesystems/problem_034_removing_empty_lines_from_a_text_file.h"

#include <filesystem>
#include <fstream>
#include <ios>  // in, out
#include <iostream>  // cout
#include <regex>  // regex_search


// Removing empty lines from a text file
//
// Write a program that, given the path to a text file, modifies the file by removing all empty lines.
// Lines containing only whitespaces are considered empty.
void problem_34_main()
{
    const auto in_path{ std::filesystem::current_path() / "res" / "problem34.txt" };
    const auto temp_path{ std::filesystem::current_path() / "res" / "problem34-tmp.txt" };

    std::fstream in_f(in_path, std::ios::in);
    std::fstream temp_f(temp_path, std::ios::out);

    std::string line{};
    bool first{ true };  // to avoid writing a blank line at the end of the new file
    while (std::getline(in_f, line))
    {
        const std::regex pattern(R"(^[[:space:]]*$)");
        if (not std::regex_search(line, pattern))
        {
            temp_f << (first ? "" : "\n") << line;
        }
        first = false;
    }

    in_f.close();
    temp_f.close();

    //std::filesystem::rename(temp_path, in_path);  // commented out so that we don't really overwrite input file

    std::cout << "\n";
}
