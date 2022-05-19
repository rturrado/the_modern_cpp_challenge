#include "chapter_06_algorithms_and_data_structures/problem_049_text_histogram.h"

#include <algorithm>  // for_each
#include <cctype>  // isalpha
#include <exception>
#include <filesystem>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fstream>  // ifstream
#include <iostream>  // cout
#include <map>
#include <numeric>  // accumulate
#include <stdexcept>  // runtime_error
#include <string>  // getline


letter_counts count_letters(std::ifstream& in_file) {
    letter_counts ret{};
    std::string line{};
    while (std::getline(in_file, line)) {
        for (auto& c : line) {
            // Like all other functions from <cctype>, the behavior of std::isalpha is undefined
            // if the argument's value is neither representable as unsigned char nor equal to EOF.
            // To use these functions safely with plain chars (or signed chars),
            // the argument should first be converted to unsigned char.
            //
            // From CppReference: https://en.cppreference.com/w/cpp/string/byte/isalpha
            if (std::isalpha(static_cast<unsigned char>(c))) {
                ret[c]++;
            }
        }
    }
    return ret;
}


void print_histogram(std::ostream& os, letter_counts& counts) {
    const size_t histogram_width{ 300 };

    size_t total_count = std::accumulate(cbegin(counts), cend(counts), static_cast<size_t>(0),
        [](auto total, auto& kvp) { return total + kvp.second; });

    auto print_histogram_line = [&os, &histogram_width, &total_count](char c, size_t count) {
        double frequency{ (count * 100.0) / total_count };

        // Subtract 12 for line header, e.g.: 'e (13.25 %) '
        size_t bar_width{ static_cast<size_t>(((histogram_width - 12) * frequency) / 100) };

        fmt::print(os, "{} ({:5.2f} %) {:=>{}}\n", c, frequency, '>', bar_width);
    };

    std::for_each(cbegin(counts), cend(counts), [&print_histogram_line](const auto& kvp) {
        print_histogram_line(kvp.first, kvp.second);
    });
}


void problem_49_main(std::ostream& os)
{
    namespace fs = std::filesystem;

    try {
        fs::path in_file_path{ fs::current_path() / "res" / "sample_file.txt"};
        std::ifstream in_file{ in_file_path };
        if (not in_file) {
            throw std::runtime_error{ fmt::format("file not found: {}, from current path: {}",
                in_file_path.generic_string(), fs::current_path().generic_string()) };
        }

        // Count letters
        auto counts{ count_letters(in_file) };

        // Print histogram
        print_histogram(os, counts);
    }
    catch (const std::exception& err) {
        fmt::print(os, "Error: {}\n", err.what());
    }

    fmt::print(os, "\n");
}


// Text histogram
//
// Write a program that, given a text, determines and prints a histogram with the frequency of each letter of the alphabet.
// The frequency is the percentage of the number of appearances of each letter from the total count of letters.
// The program should count only the appearances of letters and ignore digits, signs, and other possible characters.
// The frequency must be determined based on the count of letters and not the text size.
void problem_49_main() {
    problem_49_main(std::cout);
}
