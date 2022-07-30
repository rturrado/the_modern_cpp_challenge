#include "chapter_12_networking_and_services/text_translation.h"
#include "text_translation_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>
#include <variant>  // get, holds_alternative

using namespace tmcppc::text_translation;


TEST(translator, DISABLED_translate_and_provider_returned_an_error_response) {
    provider_mock provider{};
    std::string_view text{ "It was a wrong number that started it, the telephone ringing three times in the dead of night." };
    auto from_code{ language_code::English };
    auto to_code{ language_code::Spanish };
    EXPECT_CALL(provider, translate(text, from_code, to_code))
        .WillOnce(::testing::Return(
            R"(<html><body><h1>Argument Exception</h1>)"
            R"(<p>Method: Translate()</p>)"
            R"(<p>Parameter: </p><p>Message: Invalid Azure Subscription key.</p>)"
            R"(<code></code>)"
            R"(<p>message id=V2_Rest_Translate.BNZE.1C19.0730T1725.B03984</p></body></html>)"
        ));
    const auto& result{ translator{ provider }.translate(text, from_code, to_code) };
    EXPECT_TRUE(std::holds_alternative<error_response>(result));
    EXPECT_EQ(std::get<error_response>(result).text, "Invalid Azure Subscription key.");
}


TEST(translator, DISABLED_translate_and_provider_returned_a_translation_response) {
    provider_mock provider{};
    std::string_view text{ "It was a wrong number that started it, the telephone ringing three times in the dead of night." };
    auto from_code{ language_code::English };
    auto to_code{ language_code::Spanish };
    EXPECT_CALL(provider, translate(text, from_code, to_code))
        .WillOnce(::testing::Return(fmt::format("{}",
            R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
            "Fue un número equivocado lo que lo inició, el teléfono sonó tres veces en la oscuridad de la noche."
            R"(</string>)"
        )));
    const auto& result{ translator{ provider }.translate(text, from_code, to_code) };
    EXPECT_TRUE(std::holds_alternative<translation_response>(result));
    EXPECT_EQ(std::get<translation_response>(result).text, fmt::format("{}",
        "Fue un número equivocado lo que lo inició, el teléfono sonó tres veces en la oscuridad de la noche."
    ));
}
