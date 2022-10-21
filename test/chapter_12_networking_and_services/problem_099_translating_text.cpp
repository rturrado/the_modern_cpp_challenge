#include "chapter_12_networking_and_services/text_translation.h"
#include "chapter_12_networking_and_services/text_translation/samples.h"
#include "chapter_12_networking_and_services/problem_099_translating_text.h"
#include "text_translation/mock.h"
#include "text_translation/samples.h"

#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>  // make_unique, unique_ptr
#include <string_view>
#include <utility>  // move

using namespace tmcppc::text_translation;


TEST(test_text_translation, output) {
    std::unique_ptr<provider_adaptor> provider_up{ std::make_unique<provider_mock>() };
    auto& provider{ *(dynamic_cast<provider_mock*>(provider_up.get())) };
    EXPECT_CALL(provider, translate(samples::english, language_code::English, language_code::Arabic))
        .WillOnce(::testing::Return(samples::provider_response_text::arabic));
    EXPECT_CALL(provider, translate(samples::english, language_code::English, language_code::German))
        .WillOnce(::testing::Return(samples::provider_response_text::german));
    EXPECT_CALL(provider, translate(samples::english, language_code::English, language_code::Greek))
        .WillOnce(::testing::Return(samples::provider_response_text::greek));
    EXPECT_CALL(provider, translate(samples::english, language_code::English, language_code::Spanish))
        .WillOnce(::testing::Return(samples::provider_response_text::spanish));
    EXPECT_CALL(provider, translate(samples::english, language_code::English, language_code::French))
        .WillOnce(::testing::Return(samples::provider_response_text::french));
    EXPECT_CALL(provider, translate(samples::english, language_code::English, language_code::Italian))
        .WillOnce(::testing::Return(samples::provider_response_text::italian));
    EXPECT_CALL(provider, translate(samples::english, language_code::English, language_code::Polish))
        .WillOnce(::testing::Return(samples::provider_response_text::polish));
    EXPECT_CALL(provider, translate(samples::english, language_code::English, language_code::Portuguese_Portugal))
        .WillOnce(::testing::Return(samples::provider_response_text::portuguese_portugal));
    EXPECT_CALL(provider, translate(samples::english, language_code::English, language_code::Chinese_Simplified))
        .WillOnce(::testing::Return(samples::provider_response_text::chinese_simplified));

    std::ostringstream oss{};
    tmcppc::problem_99::test_text_translation(oss, translator{ std::move(provider_up) });

    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        fmt::format(
            "\ten: {}\n"
            "\tar: {}\n"
            "\tde: {}\n"
            "\tel: {}\n"
            "\tes: {}\n"
            "\tfr: {}\n"
            "\tit: {}\n"
            "\tpl: {}\n"
            "\tpt-pt: {}\n"
            "\tzh-Hans: {}\n\n",
            samples::english,
            samples::arabic_output,
            samples::german_output,
            samples::greek_output,
            samples::spanish_output,
            samples::french_output,
            samples::italian_output,
            samples::polish_output,
            samples::portuguese_portugal_output,
            samples::chinese_simplified_output
        )
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
