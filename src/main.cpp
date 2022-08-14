#include "env.h"
#include "problems.h"

#include <charconv>  // from_chars
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cin, cout
#include <ostream>
#include <string>  // getline
#include <system_error>  // errc

namespace fs = std::filesystem;


void print_usage(std::ostream& os) {
    fmt::print(os, "Usage:\n");
    fmt::print(os, "\tthe_modern_c++_challenge <RESOURCE_DIR_PATH>\n");
    fmt::print(os, "\n");
    fmt::print(os, "Where:\n");
    fmt::print(os, "\tRESOURCE_DIR_PATH  Path to the resource folder (relative or absolute)\n");
    fmt::print(os, "Example:\n");
    fmt::print(os, "\tthe_modern_c++_challenge ../res\n");
}


int main_impl(int argc, char** argv, std::istream& is, std::ostream& os) {
    if (argc != 2) {
        print_usage(os);
        return 1;
    }
    const fs::path resource_folder_path{ argv[1] };
    if (not fs::exists(resource_folder_path)) {
        fmt::print(os, "Error: path '{}' does not exist\n", resource_folder_path.generic_string());
        return 1;
    }
    if (not fs::is_directory(resource_folder_path)) {
        fmt::print(os, "Error: path '{}' is not a directory\n", resource_folder_path.generic_string());
        return 1;
    }
    tmcppc::env::get_instance().set_resource_folder_path(fs::absolute(resource_folder_path));

    problems& problems{ problems::get_instance() };

    try {
        while (true) {
            fmt::print(os,
                "What problem do you want to run? "
                "Please enter a number between {} and {} ('quit' to exit): ",
                1, problems.size());

            std::string input{};
            std::getline(is, input);
            if (input == "quit") {
                break;
            }

            int problem_number{};
            auto [ptr, ec] { std::from_chars(input.data(), input.data() + input.size(), problem_number)};
            if (ec == std::errc{}) {
                if (1 <= problem_number and problem_number <= problems.size()) {
                    fmt::print(os, "\n[PROBLEM {}]\n", problem_number);
                    problems.execute(problem_number);
                } else {
                    fmt::print(os, "\tError: number not within the limits\n");
                }
            } else {
                fmt::print(os, "\tError: invalid input\n");
            }
        }
    } catch (const std::exception& ex) {
        fmt::print("Error: {}\n", ex.what());
        return 1;
    }
    return 0;
}


int main(int argc, char** argv) {
    return main_impl(argc, argv, std::cin, std::cout);
}
