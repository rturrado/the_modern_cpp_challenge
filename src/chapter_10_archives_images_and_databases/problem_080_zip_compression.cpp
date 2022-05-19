#include "chapter_10_archives_images_and_databases/zip_lib_wrapper.h"

#include <iostream>  // cin, cout
#include <istream>
#include <ostream>


void problem_80_main(std::istream& is, std::ostream& os) {
    tmcppc::zip_lib::test(is, os);
}

// Compressing and decompressing files to/from a ZIP archive
//
// Write a program that can do the following:
//   - Compress either a file or the contents of a user-specified directory, recursively, to a ZIP archive.
//   - Decompress the contents of a ZIP archive to a user-specified destination directory.
void problem_80_main() {
    problem_80_main(std::cin, std::cout);
}
