#include "chapter_11_cryptography/problem_093_aes_encryption.h"
#include "env.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/default.h>  // DefaultDecryptorWithMac, DefaultEncryptorWithMAC
#include <cryptopp/files.h>  // FileSink, FileSource
#include <cryptopp/hex.h>  // HexDecoder, HexEncoder
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <rtc/filesystem.h>
#include <string>

namespace fs = std::filesystem;


namespace tmcppc::crypto {
    void aes_encrypt(const fs::path& input_file_path, const fs::path& encrypted_file_path, const std::string& password) {
        if (not fs::exists(input_file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ input_file_path.generic_string() };
        }

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
    }

    void aes_decrypt(const fs::path& encrypted_file_path, const fs::path& decrypted_file_path, const std::string& password) {
        if (not fs::exists(encrypted_file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ encrypted_file_path.generic_string() };
        }

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
    }
}  // namespace tmcppc::crypto


void problem_93_main(std::ostream& os) {
    using namespace tmcppc::crypto;

    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    const auto encrypted_file_path{ fs::temp_directory_path() / "calibri.ttf.encrypted" };
    const auto decrypted_file_path{ fs::temp_directory_path() / "calibri.ttf.decrypted" };
    const std::string password{ "Super secret password" };

    fmt::print(os, "Encrypting and decrypting file '{}'\n", input_file_path.generic_string());
    fmt::print(os, "Using AES and password '{}'\n", password);

    aes_encrypt(input_file_path, encrypted_file_path, password);
    aes_decrypt(encrypted_file_path, decrypted_file_path, password);

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
