#include "chapter_11_cryptography/problem_093_aes_encryption.h"
#include "env.h"

#include "rtc/filesystem.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>
#include <string>

#include "cryptopp/cryptlib.h"
#include "cryptopp/default.h"  // DefaultDecryptorWithMac, DefaultEncryptorWithMAC
#include "cryptopp/files.h"  // FileSink, FileSource
#include "cryptopp/hex.h"  // HexDecoder, HexEncoder


void problem_93_main(std::ostream& os) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    const auto encrypted_file_path{ std::filesystem::temp_directory_path() / "calibri.ttf.encrypted" };
    const auto decrypted_file_path{ std::filesystem::temp_directory_path() / "calibri.ttf.decrypted" };
    const std::string password{ "Super secret password" };

    fmt::print(os, "Encrypting and decrypting file '{}'\n", input_file_path.generic_string());
    fmt::print(os, "Using AES and password '{}'\n", password);

    CryptoPP::FileSource input_file_source{
        input_file_path.c_str(),
        true,
        new CryptoPP::DefaultEncryptorWithMAC{
            reinterpret_cast<const CryptoPP::byte*>(password.data()),
            password.size(),
            new CryptoPP::HexEncoder{
                new CryptoPP::FileSink{encrypted_file_path.c_str()}
            }
        }
    };

    CryptoPP::FileSource encrypted_file_source{
        encrypted_file_path.c_str(),
        true,
        new CryptoPP::HexDecoder{
            new CryptoPP::DefaultDecryptorWithMAC{
                reinterpret_cast<const CryptoPP::byte*>(password.data()),
                password.size(),
                new CryptoPP::FileSink{decrypted_file_path.c_str()}
            }
        }
    };

    if (rtc::filesystem::get_binary_file_content(input_file_path) ==
        rtc::filesystem::get_binary_file_content(decrypted_file_path)) {

        fmt::print(os, "\tOK\n");
    } else {
        fmt::print(os, "\tError: the decrypted content differs from the original content\n");
    }

    fmt::print(os, "\n");
}


// Encrypting and decrypting files
//
// Write a program that can encrypt and decrypt files using the Advanced Encryption Standard (AES or Rijndael).
// It should be possible to specify both a source file and a destination file path, as well as a password.
void problem_93_main() {
    problem_93_main(std::cout);
}
