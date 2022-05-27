#pragma once

#include <filesystem>
#include <iosfwd>
#include <string>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "cryptlib.h"
#include "files.h"  // FileSource
#include "filters.h"  // HashFilter, StringSink
#include "hex.h"  // HexEncoder

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


void problem_92_main(std::ostream& os);
void problem_92_main();
