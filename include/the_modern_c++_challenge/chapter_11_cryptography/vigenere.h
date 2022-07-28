#pragma once

#include "chapter_11_cryptography/crypt.h"

#include "rtc/random.h"

#include <algorithm>  // find, for_each, generate_n, transform
#include <array>
#include <cctype>  // isalpha, islower, tolower, toupper
#include <filesystem>
#include <iterator>  // distance
#include <string>
#include <string_view>


namespace tmcppc::crypto {
    class vigenere : public crypt {
    private:
        static constexpr unsigned char letters_size_{ 26 };
        using square_t = std::array<std::array<unsigned char, letters_size_>, letters_size_>;

        [[nodiscard]] static consteval square_t build_square() {
            square_t ret{};

            unsigned char letter{ 'a' };
            std::ranges::for_each(ret, [&letter](auto& row) {
                auto increment_letter = [](unsigned char& c) {
                    c = (c == 'z') ? 'a' : c + 1;
                };
                std::generate_n(row.begin(), row.size(), [&letter, &increment_letter]() {
                    auto ret{ letter };
                    increment_letter(letter);
                    return ret;
                });
                increment_letter(letter);
            });
            return ret;
        }

        static const square_t square_;
        std::string key_{};

    public:
        vigenere() : key_(rtc::random::random_int{ 5, 10 }(), 0) {  // [5, 10]
            std::generate_n(key_.begin(), key_.size(), []() {
                return static_cast<unsigned char>('a' + rtc::random::random_int{ 0, letters_size_ - 1 }());  // [0, letters_size - 1]
            });

        }

        [[nodiscard]] virtual std::string encrypt(std::string_view text) const override {
            auto encrypt_char = [this](unsigned char c, size_t key_index) {
                if (not std::isalpha(c)) {
                    return c;
                }
                auto lower_c{ std::tolower(c) };
                size_t row{ static_cast<size_t>(key_[key_index]) - 'a' };
                size_t col{ static_cast<size_t>(lower_c) - 'a' };
                auto ciphered_lower_c{ square_.at(row).at(col) };
                if (std::islower(c)) {
                    return ciphered_lower_c;
                }
                return static_cast<unsigned char>(std::toupper(ciphered_lower_c));
            };

            std::string ret(text.size(), 0);
            size_t key_index{ 0 };
            std::ranges::transform(text, ret.begin(),
                [this, &encrypt_char, &key_index](unsigned char c) {
                    auto ret{ encrypt_char(c, key_index) };
                    key_index = (key_index + 1) % key_.size();
                    return ret;
            });
            return ret;
        }

        [[nodiscard]] virtual std::string decrypt(std::string_view text) const override {
            auto decrypt_char = [this](unsigned char c, size_t key_index) {
                if (not std::isalpha(c)) {
                    return c;
                }
                auto lower_c{ std::tolower(c) };
                size_t row{ static_cast<size_t>(key_[key_index]) - 'a' };
                size_t col{ static_cast<size_t>(std::distance(std::begin(square_[row]), std::ranges::find(square_[row], lower_c))) };
                auto deciphered_lower_c{ static_cast<unsigned char>('a' + col) };
                if (std::islower(c)) {
                    return deciphered_lower_c;
                }
                return static_cast<unsigned char>(std::toupper(deciphered_lower_c));
            };

            std::string ret(text.size(), 0);
            size_t key_index{ 0 };
            std::ranges::transform(text, ret.begin(),
                [this, &decrypt_char, &key_index](unsigned char c) {
                    auto ret{ decrypt_char(c, key_index) };
                    key_index = (key_index + 1) % key_.size();
                    return ret;
            });
            return ret;
        }
    };
}  // namespace tmcppc::crypto
