#include "chapter_10_archives_images_and_databases/problem_081_zip_compression_with_password.h"
#include "chapter_10_archives_images_and_databases/zip/zip_lib_wrapper.h"
#include "env.h"

#include <filesystem>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>
#include <string>


void problem_81_main(std::istream& is, std::ostream& os, const std::string& password) {
    using namespace tmcppc::zip;
    namespace fs = std::filesystem;

    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto input_file_path{ resource_folder_path / "sample_folder" / "dilbert.jpg" };  // test files
    const auto input_dir_path{ resource_folder_path / "sample_folder" / "sample_subfolder" };  // and folders
    const auto output_root_path{ fs::temp_directory_path() };

    for (auto&& input_path : { input_file_path, input_dir_path }) {
        const auto output_path{ output_root_path / input_path.relative_path() };
        const auto output_relative_root_directory_path{ output_root_path / *input_path.relative_path().begin() };
        const auto zip_file_path{ create_zip_file_path(output_root_path, input_path) };

        // Input path                                c:/programming/code/c++/the_modern_c++_challenge/res/sample_folder/dilbert.jpg
        // Input relative path                          programming/code/c++/the_modern_c++_challenge/res/sample_folder/dilbert.jpg
        // Input file name                                                                                              dilbert.jpg
        // Output root path                     c:/temp
        // Output path                          c:/temp/programming/code/c++/the_modern_c++_challenge/res/sample_folder/dilbert.jpg
        // Output relative root directory path  c:/temp/programming
        // Zip file path                        c:/temp/                                                                dilbert.zip

        try {
            compress(os, input_path, zip_file_path, password);
            decompress(os, zip_file_path, output_root_path, password);
            compare_input_and_output(os, input_path, output_path);
            remove_output(is, os, output_relative_root_directory_path);
        }
        catch (const std::exception& ex) {
            fmt::print(os, "\nError: {}\n", ex.what());
        }
        fmt::print(os, "\n");
    }
}


// Compressing and decompressing files to/from a ZIP archive with a password
//
// Write a program that can do the following:
//   - Compress either a file or the contents of a user-specified directory, recursively, to a password-protected ZIP archive.
//   - Decompress the contents of a password-protected ZIP archive to a user-specified destination directory.
void problem_81_main() {
    const auto password{ std::string{ "(4n)!(1103+26390n)"} };

    problem_81_main(std::cin, std::cout, password);
}
