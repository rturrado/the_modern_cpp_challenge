#pragma once

#include <filesystem>
#include <iosfwd>


namespace tmcppc::crypto {
    void generate_keys(
        const std::filesystem::path& rsa_private_key_file_path,
        const std::filesystem::path& rsa_public_key_file_path);
    void sign_file(
        const std::filesystem::path& input_file_path,
        const std::filesystem::path& rsa_private_key_file_path,
        const std::filesystem::path& signature_file_path);
    bool verify_file(
        const std::filesystem::path& input_file_path,
        const std::filesystem::path& rsa_public_key_file_path,
        const std::filesystem::path& signature_file_path);
}  // namespace tmcppc::problem_94


void problem_94_main(std::ostream& os);
void problem_94_main();
