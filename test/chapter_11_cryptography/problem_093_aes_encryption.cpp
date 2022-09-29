#include "chapter_11_cryptography/problem_093_aes_encryption.h"
#include "env.h"

#include <filesystem>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <rtc/filesystem.h>
#include <sstream>  // ostringstream

namespace fs = std::filesystem;
using namespace tmcppc::crypto;


TEST(aes_encrypt, input_file_does_not_exist) {
    const auto encrypted_file_path{ fs::temp_directory_path() / "calibri.ttf.encrypted" };
    const std::string password{ "Super secret password" };
    EXPECT_THROW(aes_encrypt(fs::path{}, encrypted_file_path, password), rtc::filesystem::file_path_does_not_exist_error);
}
TEST(aes_encrypt, input_file_exists) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    const auto encrypted_file_path{ fs::temp_directory_path() / "calibri.ttf.encrypted" };
    const std::string password{ "Super secret password" };
    aes_encrypt(input_file_path, encrypted_file_path, password);
    EXPECT_TRUE(fs::exists(encrypted_file_path));
    EXPECT_FALSE(fs::is_empty(encrypted_file_path));
}
TEST(aes_decrypt, encrypted_file_does_not_exist) {
    const auto decrypted_file_path{ fs::temp_directory_path() / "calibri.ttf.decrypted" };
    const std::string password{ "Super secret password" };
    EXPECT_THROW(aes_decrypt(fs::path{}, decrypted_file_path, password), rtc::filesystem::file_path_does_not_exist_error);
}
TEST(aes_decrypt, encrypted_file_exists) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    const auto encrypted_file_path{ fs::temp_directory_path() / "calibri.ttf.encrypted" };
    const auto decrypted_file_path{ fs::temp_directory_path() / "calibri.ttf.decrypted" };
    const std::string password{ "Super secret password" };
    aes_encrypt(input_file_path, encrypted_file_path, password);
    aes_decrypt(encrypted_file_path, decrypted_file_path, password);
    EXPECT_TRUE(fs::exists(decrypted_file_path));
    EXPECT_FALSE(fs::is_empty(decrypted_file_path));
}


TEST(problem_93_main, output) {
    std::ostringstream oss{};
    problem_93_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Encrypting and decrypting file '.*res/fonts/calibri.ttf'\n"
        "Using AES and password 'Super secret password'\n"
        "\tOK\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
