#include "chapter_06_algorithms_and_data_structures/problem_049_text_histogram.h"
#include "env.h"

#include <algorithm>  // for_each
#include <cctype>  // isalpha
#include <exception>
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <map>
#include <numeric>  // accumulate
#include <rtc/filesystem.h>
#include <string>  // getline


namespace tmcppc::problem_49 {
    letter_counts count_letters(const std::string& text) {
        letter_counts ret{};
        // Like all other functions from <cctype>, the behavior of std::isalpha is undefined
        // if the argument's value is neither representable as unsigned char nor equal to EOF.
        // To use these functions safely with plain chars (or signed chars),
        // the argument should first be converted to unsigned char.
        //
        // From CppReference: https://en.cppreference.com/w/cpp/string/byte/isalpha
        std::ranges::for_each(text, [&ret](char c) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                ret[c]++;
            }
        });
        return ret;
    }


    void print_histogram(std::ostream& os, const letter_counts& counts) {
        const size_t histogram_width{ 300 };

        size_t total_count = std::accumulate(cbegin(counts), cend(counts), static_cast<size_t>(0),
            [](auto total, auto& kvp) { return total + kvp.second;
        });

        auto print_histogram_line = [&os, &total_count](char c, size_t count) {
            double frequency{ (static_cast<double>(count) * 100.0) / static_cast<double>(total_count) };

            // Subtract 13 for line header, e.g.: 'e ( 13.27 %) '
            size_t bar_width{ static_cast<size_t>(((histogram_width - 13) * frequency) / 100) };

            fmt::print(os, "{} ({:6.2f} %) {:=>{}}\n", c, frequency, '>', bar_width);
        };

        std::ranges::for_each(counts, [&print_histogram_line](const auto& kvp) {
            print_histogram_line(kvp.first, kvp.second);
        });
    }
}  // namespace tmcppc::problem_49


void problem_49_main(std::ostream& os) {
    namespace fs = std::filesystem;
    using namespace tmcppc::problem_49;

    try {
        fs::path in_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt"};
        if (not fs::exists(in_file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error(in_file_path.generic_string());
        }

        // Count letters
        auto counts{ count_letters(rtc::filesystem::get_text_file_content(in_file_path)) };

        // Print histogram
        print_histogram(os, counts);
    } catch (const std::exception& err) {
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
