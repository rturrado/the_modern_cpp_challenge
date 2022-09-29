#include "chapter_11_cryptography/vigenere.h"

#include <gtest/gtest.h>
#include <string_view>

using namespace std::string_view_literals;
using namespace tmcppc::crypto;


TEST(vigenere, encrypt_empty_string) {
    const auto text{ "" };
    EXPECT_EQ(vigenere{}.encrypt(text), text);
}
TEST(vigenere, encrypt_string_with_no_alphas) {
    const auto text{ "1234567890!?@#" };
    EXPECT_EQ(vigenere{}.encrypt(text), text);
}

TEST(vigenere, encrypt_and_decrypt_empty_string) {
    const auto text{ "" };
    vigenere cipher{};
    auto ret{ cipher.encrypt(text) };
    EXPECT_EQ(cipher.decrypt(ret), text);
}
TEST(vigenere, encrypt_and_decrypt_string_with_no_alphas) {
    const auto text{ "1234567890!?@#" };
    vigenere cipher{};
    auto ret{ cipher.encrypt(text) };
    EXPECT_EQ(cipher.decrypt(ret), text);
}
TEST(vigenere, encrypt_and_decrypt) {
    const auto text{ "In the beginning, there was simply the event and its consequences."sv };
    vigenere cipher{};
    auto ret{ cipher.encrypt(text) };
    EXPECT_EQ(cipher.decrypt(ret), text);
}
