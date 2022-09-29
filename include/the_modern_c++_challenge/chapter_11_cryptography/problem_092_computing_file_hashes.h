#pragma once

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>  // FileSource
#include <cryptopp/filters.h>  // HashFilter, StringSink
#include <cryptopp/hex.h>  // HexEncoder
#include <filesystem>
#include <iosfwd>
#include <rtc/filesystem.h>
#include <string>


namespace tmcppc::crypto {
    template <typename Hash>
    std::string get_hash_as_hex_string(const std::filesystem::path& file_path) {
        if (not fs::exists(file_path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ file_path.generic_string()};
        }

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
}  // namespace tmcppc::crypto


void problem_92_main(std::ostream& os);
void problem_92_main();
