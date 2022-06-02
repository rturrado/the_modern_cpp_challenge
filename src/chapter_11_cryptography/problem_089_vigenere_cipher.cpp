#include "chapter_11_cryptography/problem_089_vigenere_cipher.h"
#include "env.h"

#include "rtc/filesystem.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <memory>  // make_unique, unique_ptr
#include <ostream>


/* static */ constexpr vigenere::square_t vigenere::square_{ vigenere::build_square() };


void problem_89_main(std::ostream& os) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    const auto input_file_content{ rtc::filesystem::get_text_file_content(input_file_path) };

    const std::unique_ptr<crypt> crypt_up{ std::make_unique<vigenere>() };

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


// Vigenere cipher
//
// Write a program that can encrypt and decrypt messages using the Vigenere cipher.
// For simplicity, the input plain-text messages for encryption should consist of only uppercase letters.
void problem_89_main() {
    problem_89_main(std::cout);
}
