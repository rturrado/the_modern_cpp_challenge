#include "chapter_11_cryptography/problem_092_computing_file_hashes.h"
#include "env.h"

#include "rtc/filesystem.h"

#include "cryptopp/md5.h"  // MD5
#include "cryptopp/sha.h"  // SHA1, SHA256

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <sstream>  // ostringstream

using namespace tmcppc::crypto;
namespace fs = std::filesystem;


TEST(get_hash_as_hex_string, DISABLED_file_does_not_exist) {
    EXPECT_THROW((void) get_hash_as_hex_string<CryptoPP::SHA1>(fs::path{}), rtc::filesystem::file_path_does_not_exist_error);
}
TEST(get_hash_as_hex_string, DISABLED_sha1_of_calibri_ttf) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    EXPECT_EQ(get_hash_as_hex_string<CryptoPP::SHA1>(input_file_path), "649A1ED83F061C390FA87238303393C082360181");
}
TEST(get_hash_as_hex_string, DISABLED_sha256_of_calibri_ttf) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    EXPECT_EQ(get_hash_as_hex_string<CryptoPP::SHA256>(input_file_path),
        "198E8DAC512206F27C9BDBFEB3D5B3E55A33DE9DCF58D801823EF8C5EF5A76DC"
    );
}
TEST(get_hash_as_hex_string, DISABLED_md5_of_calibri_ttf) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    EXPECT_EQ(get_hash_as_hex_string<CryptoPP::Weak::MD5>(input_file_path), "3DEA6DA513097358F7FBB4408AACB736");
}


TEST(problem_92_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_92_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Calculating SHA1, SHA256 and MD5 for file '.*res/fonts/calibri.ttf'\n"
        "\tSHA1: '649A1ED83F061C390FA87238303393C082360181'\n"
        "\tSHA256: '198E8DAC512206F27C9BDBFEB3D5B3E55A33DE9DCF58D801823EF8C5EF5A76DC'\n"
        "\tMD5: '3DEA6DA513097358F7FBB4408AACB736'\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
