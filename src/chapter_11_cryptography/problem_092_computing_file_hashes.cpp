#include "chapter_11_cryptography.h"

#include <filesystem>
#include <format>
#include <iostream>  // cout
#include <vector>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "cryptocpp/cryptlib.h"
#include "cryptocpp/files.h"  // FileSource
#include "cryptocpp/filters.h"  // HashFilter, StringSink
#include "cryptocpp/hex.h"  // HexEncoder
#include "cryptocpp/md5.h"  // MD5
#include "cryptocpp/sha.h"  // SHA1, SHA256

namespace fs = std::filesystem;


template <typename Hash>
std::string get_hash_as_hex_string(const fs::path& file_path)
{
    std::string digest{};
    Hash hash{};

    CryptoPP::FileSource file_source{
        file_path.c_str(),
        true,
        new CryptoPP::HashFilter{hash,
            new CryptoPP::HexEncoder{
                new CryptoPP::StringSink{digest}
            }
        }
    };

    return digest;
}


// Computing file hashes
//
// Write a program that, given a path to a file, computes and prints to the console
// the SHA1, SHA256, and MD5 hash values for the content of the file.
void problem_92_main()
{
    const auto input_file_path{ std::filesystem::current_path() / "res" / "fonts" / "calibri.ttf" };

    std::cout << std::format("Calculating SHA1, SHA256 and MD5 for file '{}'\n", input_file_path.string());

    std::cout << std::format("\tSHA1: '{}'\n", get_hash_as_hex_string<CryptoPP::SHA1>(input_file_path));
    std::cout << std::format("\tSHA256: '{}'\n", get_hash_as_hex_string<CryptoPP::SHA256>(input_file_path));
    std::cout << std::format("\tMD5: '{}'\n", get_hash_as_hex_string<CryptoPP::Weak::MD5>(input_file_path));

    std::cout << "\n";
}
