#include "chapter_12_networking_and_services/text_translation.h"
#include "chapter_12_networking_and_services/text_translation/samples.h"
#include "text_translation/mock.h"
#include "text_translation/samples.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>  // make_unique, unique_ptr
#include <fmt/format.h>
#include <utility>  // move
#include <variant>  // get, holds_alternative

using namespace tmcppc::text_translation;


TEST(translator, provider_is_null) { EXPECT_THROW(translator{ nullptr }, translation_error); }


TEST(translator, translate_and_provider_returns_an_error_response) {
    std::unique_ptr<provider_adaptor> provider_up{ std::make_unique<provider_mock>() };
    auto& provider{ *(dynamic_cast<provider_mock*>(provider_up.get())) };
    std::string_view text{ samples::english };
    auto from_code{ language_code::English };
    auto to_code{ language_code::Spanish };
    EXPECT_CALL(provider, translate(text, from_code, to_code))
        .WillOnce(::testing::Return(samples::provider_response_text::error));
    const auto& result{ translator{ std::move(provider_up) }.translate(text, from_code, to_code) };
    EXPECT_TRUE(std::holds_alternative<error_response>(result));
    EXPECT_EQ(std::get<error_response>(result).text, samples::error_output);
}


TEST(translator, translate_and_provider_returns_a_translation_response) {
    std::unique_ptr<provider_adaptor> provider_up{ std::make_unique<provider_mock>() };
    auto& provider{ *(dynamic_cast<provider_mock*>(provider_up.get())) };
    std::string_view text{ samples::english };
    auto from_code{ language_code::English };
    auto to_code{ language_code::Spanish };
    EXPECT_CALL(provider, translate(text, from_code, to_code))
        .WillOnce(::testing::Return(samples::provider_response_text::spanish));
    const auto& result{ translator{ std::move(provider_up) }.translate(text, from_code, to_code) };
    EXPECT_TRUE(std::holds_alternative<translation_response>(result));
    EXPECT_EQ(std::get<translation_response>(result).text, samples::spanish_output);
}
