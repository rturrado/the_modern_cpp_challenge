#include "chapter_11_cryptography/problem_092_computing_file_hashes.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout

#include "md5.h"  // MD5
#include "sha.h"  // SHA1, SHA256

namespace fs = std::filesystem;


void problem_92_main(std::ostream& os) {
    const auto input_file_path{ fs::current_path() / "res" / "fonts" / "calibri.ttf" };

    fmt::print(os, "Calculating SHA1, SHA256 and MD5 for file '{}'\n", input_file_path.generic_string());

    fmt::print(os, "\tSHA1: '{}'\n", get_hash_as_hex_string<CryptoPP::SHA1>(input_file_path));
    fmt::print(os, "\tSHA256: '{}'\n", get_hash_as_hex_string<CryptoPP::SHA256>(input_file_path));
    fmt::print(os, "\tMD5: '{}'\n", get_hash_as_hex_string<CryptoPP::Weak::MD5>(input_file_path));

    fmt::print(os, "\n");
}


// Computing file hashes
//
// Write a program that, given a path to a file, computes and prints to the console
// the SHA1, SHA256, and MD5 hash values for the content of the file.
void problem_92_main() {
    problem_92_main(std::cout);
}
