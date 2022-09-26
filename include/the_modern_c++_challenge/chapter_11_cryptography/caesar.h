#pragma once

#include "chapter_11_cryptography/crypt.h"

#include "rtc/random.h"

#include <algorithm>  // transform
#include <cctype>  // isalpha, islower, tolower, toupper
#include <iosfwd>
#include <string>
#include <string_view>


namespace tmcppc::crypto {
    class caesar : public crypt {
    private:
        static inline const unsigned char letters_size_{ 26 };
        unsigned char shift_value_{};

    public:
        caesar() : shift_value_{ static_cast<unsigned char>(rtc::random::random_int{0, letters_size_ - 1}()) } {}

        [[nodiscard]] std::string encrypt(std::string_view text) const override {
            auto encrypt_char = [this](unsigned char c) {
                if (not std::isalpha(c)) {
                    return c;
                }
                auto ciphered_lower_c_index{ (std::tolower(c) - 'a' + shift_value_) % letters_size_ };
                auto ciphered_lower_c{ 'a' + ciphered_lower_c_index };
                if (std::islower(c)) {
                    return static_cast<unsigned char>(ciphered_lower_c);
                }
                return static_cast<unsigned char>(std::toupper(ciphered_lower_c));
            };

            std::string ret(text.size(), 0);
            std::ranges::transform(text, ret.begin(), [&encrypt_char](unsigned char c) {
                return encrypt_char(c);
            });
            return ret;
        }

        [[nodiscard]] std::string decrypt(std::string_view text) const override {
            auto decrypt_char = [this](unsigned char c) {
                if (not std::isalpha(c)) {
                    return c;
                }
                auto deciphered_lower_c_index{ (std::tolower(c) - 'a' + letters_size_ - shift_value_) % letters_size_ };
                auto deciphered_lower_c{ 'a' + deciphered_lower_c_index };
                if (std::islower(c)) {
                    return static_cast<unsigned char>(deciphered_lower_c);
                }
                return static_cast<unsigned char>(std::toupper(deciphered_lower_c));
            };

            std::string ret(text.size(), 0);
            std::ranges::transform(text, ret.begin(), [&decrypt_char](unsigned char c) {
                return decrypt_char(c);
            });
            return ret;
        }
    };
}  // namespace tmcppc::crypto
