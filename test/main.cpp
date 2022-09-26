#include "env.h"

#include "gtest/gtest.h"

#include "fmt/ostream.h"

#include <filesystem>
#include <iostream>  // cout
#include <system_error>  // errc

namespace fs = std::filesystem;


void print_usage(std::ostream& os) {
    fmt::print(os, "Usage:\n");
    fmt::print(os, "\tthe_modern_c++_challenge_test <RESOURCE_DIR_PATH>\n");
    fmt::print(os, "\n");
    fmt::print(os, "Where:\n");
    fmt::print(os, "\tRESOURCE_DIR_PATH  Path to the resource folder (relative or absolute)\n");
    fmt::print(os, "Example:\n");
    fmt::print(os, "\tthe_modern_c++_challenge_test ../res\n");
}


int main_impl(int argc, char** argv, std::ostream& os) {
    ::testing::InitGoogleTest(&argc, argv);

    if (argc != 2) {
        print_usage(os);
        return 0;
    }
    const fs::path resource_folder_path{ argv[1] };
    if (not fs::exists(resource_folder_path)) {
        fmt::print(os, "Error: path '{}' does not exist\n", resource_folder_path.generic_string());
        return 0;
    }
    if (not fs::is_directory(resource_folder_path)) {
        fmt::print(os, "Error: path '{}' is not a directory\n", resource_folder_path.generic_string());
        return 0;
    }
    tmcppc::env::get_instance().set_resource_folder_path(fs::absolute(resource_folder_path));

    return RUN_ALL_TESTS();
}


int main(int argc, char** argv) {
    return main_impl(argc, argv, std::cout);
}
