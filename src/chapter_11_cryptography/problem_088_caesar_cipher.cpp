#include "chapter_11_cryptography.h"
#include "chapter_11_cryptography/Crypt.h"

#include "rtc/random.h"
#include "rtc/filesystem.h"

#include <algorithm>  // transform
#include <cctype>  // isalpha, islower, tolower, toupper
#include <filesystem>
#include <format>
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <memory>  // make_unique, unique_ptr
#include <string>
#include <string_view>


class Caesar : public Crypt
{
private:
    static inline const unsigned char letters_size_{ 26 };
    unsigned char shift_value_{};

public:
    Caesar() : shift_value_{ static_cast<unsigned char>(rtc::random::random_int{0, letters_size_ - 1}()) } {}

    [[nodiscard]] virtual std::string encrypt(std::string_view text) const override
    {
        auto encrypt_char = [this](unsigned char c) {
            if (not std::isalpha(c)) { return c; }
            auto ciphered_lower_c_index{ (std::tolower(c) - 'a' + shift_value_) % letters_size_};
            auto ciphered_lower_c{ 'a' + ciphered_lower_c_index };
            if (std::islower(c)) { return static_cast<unsigned char>(ciphered_lower_c); }
            return static_cast<unsigned char>(std::toupper(ciphered_lower_c));
        };

        std::string ret{};
        std::ranges::transform(text, std::back_inserter(ret), [&encrypt_char](unsigned char c) { return encrypt_char(c); });
        return ret;
    }

    [[nodiscard]] virtual std::string decrypt(std::string_view text) const override
    {
        auto decrypt_char = [this](unsigned char c) {
            if (not std::isalpha(c)) { return c; }
            auto deciphered_lower_c_index{ (std::tolower(c) - 'a' + letters_size_ - shift_value_) % letters_size_ };
            auto deciphered_lower_c{ 'a' + deciphered_lower_c_index };
            if (std::islower(c)) { return static_cast<unsigned char>(deciphered_lower_c); }
            return static_cast<unsigned char>(std::toupper(deciphered_lower_c));
        };

        std::string ret{};
        std::ranges::transform(text, std::back_inserter(ret), [&decrypt_char](unsigned char c) { return decrypt_char(c); });
        return ret;
    }
};


// Caesar cipher
//
// Write a program that can encrypt and decrypt messages using a Caesar cypher with a right rotation and any shift value.
// For simplicity, the program should consider only uppercase text messages and only encode letters,
// ignoring digits, symbols, and other types of characters.
void problem_88_main()
{
    const auto input_file_path{ std::filesystem::current_path() / "res" / "sample.txt" };

    const auto input_file_content{ rtc::filesystem::get_text_file_content(input_file_path) };

    const std::unique_ptr<Crypt> crypt_up{ std::make_unique<Caesar>() };

    std::cout << std::format("Encrypting and decrypting file '{}'\n", input_file_path.string());
    const auto encrypted_file_content{ crypt_up->encrypt(input_file_content) };
    const auto decrypted_file_content{ crypt_up->decrypt(encrypted_file_content) };

    if (input_file_content == decrypted_file_content) { std::cout << "\tOK\n"; }
    else { std::cout << "\tError: the decrypted content differs from the original content\n"; }

    std::cout << "\n";
}
