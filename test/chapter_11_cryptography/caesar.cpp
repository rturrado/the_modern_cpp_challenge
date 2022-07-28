#include "chapter_11_cryptography/caesar.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string_view>

using namespace std::string_view_literals;
using namespace tmcppc::crypto;


TEST(caesar, DISABLED_encrypt_empty_string) {
    const auto text{ "" };
    EXPECT_EQ(caesar{}.encrypt(text), text);
}
TEST(caesar, DISABLED_encrypt_string_with_no_alphas) {
    const auto text{ "1234567890!?@#" };
    EXPECT_EQ(caesar{}.encrypt(text), text);
}

TEST(caesar, DISABLED_encrypt_and_decrypt_empty_string) {
    const auto text{ "" };
    caesar cipher{};
    auto ret{ cipher.encrypt(text) };
    EXPECT_EQ(cipher.decrypt(ret), text);
}
TEST(caesar, DISABLED_encrypt_and_decrypt_string_with_no_alphas) {
    const auto text{ "1234567890!?@#" };
    caesar cipher{};
    auto ret{ cipher.encrypt(text) };
    EXPECT_EQ(cipher.decrypt(ret), text);
}
TEST(caesar, DISABLED_encrypt_and_decrypt) {
    const auto text{ "In the beginning, there was simply the event and its consequences."sv };
    caesar cipher{};
    auto ret{ cipher.encrypt(text) };
    EXPECT_EQ(cipher.decrypt(ret), text);
}
