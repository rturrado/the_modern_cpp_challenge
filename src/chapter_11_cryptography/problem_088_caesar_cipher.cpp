#include "chapter_11_cryptography/problem_088_caesar_cipher.h"

#include "rtc/filesystem.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <memory>  // make_unique, unique_ptr
#include <ostream>


void problem_88_main(std::ostream& os) {
    const auto input_file_path{ std::filesystem::current_path() / "res" / "sample.txt" };
    const auto input_file_content{ rtc::filesystem::get_text_file_content(input_file_path) };

    const std::unique_ptr<crypt> crypt_up{ std::make_unique<caesar>() };

    fmt::print(os, "Encrypting and decrypting file '{}'\n", input_file_path.generic_string());
    const auto encrypted_file_content{ crypt_up->encrypt(input_file_content) };
    const auto decrypted_file_content{ crypt_up->decrypt(encrypted_file_content) };

    if (input_file_content == decrypted_file_content) {
        fmt::print(os, "\tOK\n");
    } else {
        fmt::print(os, "\tError: the decrypted content differs from the original content\n");
    }

    fmt::print(os, "\n");
}


// Caesar cipher
//
// Write a program that can encrypt and decrypt messages using a Caesar cypher with a right rotation and any shift value.
// For simplicity, the program should consider only uppercase text messages and only encode letters,
// ignoring digits, symbols, and other types of characters.
void problem_88_main() {
    problem_88_main(std::cout);
}
