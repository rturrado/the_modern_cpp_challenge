#include "chapter_10_archives_images_and_databases/problem_081_zip_compression_with_password.h"
#include "chapter_10_archives_images_and_databases/zip_lib_wrapper.h"

#include <iostream>  // cin, cout
#include <istream>
#include <ostream>


void problem_81_main(std::istream& is, std::ostream& os) {
    const auto password{ std::string{ "(4n)!(1103+26390n)"} };
    
    tmcppc::zip_lib::test(is, os, password);
}


// Compressing and decompressing files to/from a ZIP archive with a password
//
// Write a program that can do the following:
//   - Compress either a file or the contents of a user-specified directory, recursively, to a password-protected ZIP archive.
//   - Decompress the contents of a password-protected ZIP archive to a user-specified destination directory.
void problem_81_main() {
    problem_81_main(std::cin, std::cout);
}
