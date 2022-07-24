#include "chapter_10_archives_images_and_databases/problem_080_zip_compression.h"
#include "chapter_10_archives_images_and_databases/problem_081_zip_compression_with_password.h"
#include "chapter_10_archives_images_and_databases/zip/zip_lib_wrapper.h"

#include <iostream>  // cin, cout
#include <istream>
#include <ostream>


void problem_80_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::problem_81;

    // Problem 81 tests compression-to and decompression-from ZIP files
    test_zip_lib(is, os);
}


// Compressing and decompressing files to/from a ZIP archive
//
// Write a program that can do the following:
//   - Compress either a file or the contents of a user-specified directory, recursively, to a ZIP archive.
//   - Decompress the contents of a ZIP archive to a user-specified destination directory.
void problem_80_main() {
    problem_80_main(std::cin, std::cout);
}
