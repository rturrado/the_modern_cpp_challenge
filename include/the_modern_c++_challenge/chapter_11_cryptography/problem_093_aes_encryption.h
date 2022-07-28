#pragma once

#include <filesystem>
#include <iosfwd>
#include <string>


namespace tmcppc::crypto {
    void aes_encrypt(const std::filesystem::path& input_file_path, const std::filesystem::path& encrypted_file_path,
        const std::string& password);
    void aes_decrypt(const std::filesystem::path& encrypted_file_path, const std::filesystem::path& decrypted_file_path,
        const std::string& password);
}  // namespace tmcppc::crypto



void problem_93_main(std::ostream& os);
void problem_93_main();
