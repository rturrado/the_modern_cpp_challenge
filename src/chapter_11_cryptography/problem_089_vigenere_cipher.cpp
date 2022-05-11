#include "chapter_11_cryptography.h"
#include "chapter_11_cryptography/Crypt.h"

#include "rtc/filesystem.h"
#include "rtc/random.h"

#include <algorithm>  // for_each, generate_n, transform
#include <array>
#include <cctype>  // isalpha, islower, tolower, toupper
#include <filesystem>
#include <format>
#include <iostream>  // cout
#include <iterator>  // back_inserter, distance
#include <memory>  // make_unique, unique_ptr
#include <string>
#include <string_view>


class Vigenere : public Crypt
{
private:
    static constexpr unsigned char letters_size_{ 26 };
    using square_t = std::array<std::array<unsigned char, letters_size_>, letters_size_>;

    [[nodiscard]] static consteval square_t build_square()
    {
        square_t ret{};

        unsigned char letter{ 'a' };
        std::ranges::for_each(ret, [&letter](auto& row) {
            auto increment_letter = [](unsigned char& c) {
                c = (c == 'z') ? 'a' : c + 1;
            };
            std::generate_n(std::begin(row), row.size(), [&letter]() {
                auto ret{ letter };
                letter = (letter == 'z') ? 'a' : letter + 1;
                return ret;
                });
            letter = (letter == 'z') ? 'a' : letter + 1;
            });
        return ret;
    }

    static const square_t square_;
    std::string key_{};

public:
    Vigenere()
    {
        auto key_size{ rtc::random::random_int{5, 10}() };

        std::generate_n(std::back_inserter(key_), key_size, []() {
            return static_cast<unsigned char>('a' + rtc::random::random_int{ 0, letters_size_ - 1 }());
            });

    }

    [[nodiscard]] virtual std::string encrypt(std::string_view text) const override
    {
        auto encrypt_char = [this](unsigned char c, size_t key_index) {
            if (not std::isalpha(c)) { return c; }
            auto lower_c{ std::tolower(c) };
            size_t row{ static_cast<size_t>(key_[key_index]) - 'a' };
            size_t col{ static_cast<size_t>(lower_c) - 'a' };
            auto ciphered_lower_c{ square_.at(row).at(col)};
            if (std::islower(c)) { return ciphered_lower_c; }
            return static_cast<unsigned char>(std::toupper(ciphered_lower_c));
        };

        std::string ret{};
        size_t key_index{ 0 };
        std::ranges::transform(text, std::back_inserter(ret),
            [this, &encrypt_char, &key_index](unsigned char c) {
                auto ret{ encrypt_char(c, key_index) };
                key_index = (key_index + 1) % key_.size();
                return ret;
            });
        return ret;
    }

    [[nodiscard]] virtual std::string decrypt(std::string_view text) const override
    {
        auto decrypt_char = [this](unsigned char c, size_t key_index) {
            if (not std::isalpha(c)) { return c; }
            auto lower_c{ std::tolower(c) };
            size_t row{ static_cast<size_t>(key_[key_index]) - 'a' };
            size_t col{ static_cast<size_t>(std::distance(std::begin(square_[row]), std::ranges::find(square_[row], lower_c))) };
            auto deciphered_lower_c{ static_cast<unsigned char>('a' + col) };
            if (std::islower(c)) { return deciphered_lower_c; }
            return static_cast<unsigned char>(std::toupper(deciphered_lower_c));
        };

        std::string ret{};
        size_t key_index{ 0 };
        std::ranges::transform(text, std::back_inserter(ret),
            [this, &decrypt_char, &key_index](unsigned char c) {
                auto ret{ decrypt_char(c, key_index) };
                key_index = (key_index + 1) % key_.size();
                return ret;
            });
        return ret;
    }
};
/* static */ constexpr Vigenere::square_t Vigenere::square_{ Vigenere::build_square() };


// Vigenere cipher
//
// Write a program that can encrypt and decrypt messages using the Vigenere cipher.
// For simplicity, the input plain-text messages for encryption should consist of only uppercase letters.
void problem_89_main()
{
    const auto input_file_path{ std::filesystem::current_path() / "res" / "sample.txt" };

    const auto input_file_content{ rtc::filesystem::get_text_file_content(input_file_path) };

    const std::unique_ptr<Crypt> crypt_up{ std::make_unique<Vigenere>() };

    std::cout << std::format("Encrypting and decrypting file '{}'\n", input_file_path.string());
    const auto encrypted_file_content{ crypt_up->encrypt(input_file_content) };
    const auto decrypted_file_content{ crypt_up->decrypt(encrypted_file_content) };

    if (input_file_content == decrypted_file_content) { std::cout << "\tOK\n"; }
    else { std::cout << "\tError: the decrypted content differs from the original content\n"; }

    std::cout << "\n";
}
