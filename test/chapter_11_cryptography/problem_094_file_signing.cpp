#include "chapter_11_cryptography/problem_094_file_signing.h"
#include "env.h"

#include "rtc/filesystem.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <filesystem>
#include <sstream>  // ostringstream

using namespace tmcppc::crypto;
namespace fs = std::filesystem;


TEST(generate_keys, ok) {
    const auto rsa_private_key_file_path{ fs::temp_directory_path() / "private_key.txt" };
    const auto rsa_public_key_file_path{ fs::temp_directory_path() / "public_key.txt" };

    generate_keys(rsa_private_key_file_path, rsa_public_key_file_path);
    EXPECT_TRUE(fs::exists(rsa_private_key_file_path));
    EXPECT_TRUE(fs::exists(rsa_public_key_file_path));
    EXPECT_FALSE(fs::is_empty(rsa_private_key_file_path));
    EXPECT_FALSE(fs::is_empty(rsa_public_key_file_path));
}


TEST(sign_file, input_file_does_not_exist) {
    const auto rsa_private_key_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "crypto" / "private_key.txt" };
    const auto signature_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "crypto" / "signature.txt" };

    EXPECT_THROW(sign_file(fs::path{}, rsa_private_key_file_path, signature_file_path), rtc::filesystem::file_path_does_not_exist_error);
}
TEST(sign_file, private_key_file_does_not_exist) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    const auto signature_file_path{ fs::temp_directory_path() / "signature.txt" };

    EXPECT_THROW(sign_file(input_file_path, fs::path{}, signature_file_path), rtc::filesystem::file_path_does_not_exist_error);
}
TEST(sign_file, ok) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    const auto rsa_private_key_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "crypto" / "private_key.txt" };
    const auto signature_file_path{ fs::temp_directory_path() / "signature.txt" };

    sign_file(input_file_path, rsa_private_key_file_path, signature_file_path);
    EXPECT_TRUE(fs::exists(signature_file_path));
    EXPECT_FALSE(fs::is_empty(signature_file_path));
}


TEST(verify_file, input_file_does_not_exist) {
    const auto rsa_private_key_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "crypto" / "private_key.txt" };
    const auto signature_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "crypto" / "signature.txt" };

    EXPECT_THROW(verify_file(fs::path{}, rsa_private_key_file_path, signature_file_path), rtc::filesystem::file_path_does_not_exist_error);
}
TEST(verify_file, public_key_file_does_not_exist) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    const auto signature_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "crypto" / "signature.txt" };

    EXPECT_THROW(verify_file(input_file_path, fs::path{}, signature_file_path), rtc::filesystem::file_path_does_not_exist_error);
}
TEST(verify_file, signature_file_does_not_exist) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    const auto rsa_public_key_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "crypto" / "public_key.txt" };

    EXPECT_THROW(verify_file(input_file_path, rsa_public_key_file_path, fs::path{}), rtc::filesystem::file_path_does_not_exist_error);
}
TEST(verify_file, ok) {
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "fonts" / "calibri.ttf" };
    const auto rsa_public_key_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "crypto" / "public_key.txt" };
    const auto signature_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "crypto" / "signature.txt" };

    EXPECT_TRUE(verify_file(input_file_path, rsa_public_key_file_path, signature_file_path));
}


TEST(problem_94_main, output) {
    std::ostringstream oss{};
    problem_94_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Generating private and public key files\n"
        "\tPrivate key file: '.*private_key.txt'\n"
        "\tPublic key file: '.*public_key.txt'\n"
        "Signing file with private key\n"
        "\tInput file: '.*res/fonts/calibri.ttf'\n"
        "\tSignature file: '.*signature.txt'\n"
        "Verifying file with public key\n"
        "\tOK\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
