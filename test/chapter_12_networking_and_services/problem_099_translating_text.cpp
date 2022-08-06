#include "chapter_12_networking_and_services/text_translation.h"
#include "chapter_12_networking_and_services/problem_099_translating_text.h"
#include "text_translation/mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>
#include <memory>  // make_unique, unique_ptr
#include <sstream>  // ostringstream
#include <string_view>

using namespace tmcppc::text_translation;


TEST(test_text_translation, output) {
    std::string_view text{ "It was a wrong number that started it, the telephone ringing three times in the dead of night." };
    std::unique_ptr<provider_adaptor> provider_up{ std::make_unique<provider_mock>() };
    auto& provider{ *(dynamic_cast<provider_mock*>(provider_up.get())) };
    EXPECT_CALL(provider, translate(text, language_code::English, language_code::Arabic))
        .WillOnce(::testing::Return(fmt::format("{}",
            R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
            "كان رقما خاطئا هو الذي بدأه ، الهاتف يرن ثلاث مرات في جوف الليل."
            R"(</string>)"
        )));
    EXPECT_CALL(provider, translate(text, language_code::English, language_code::German))
        .WillOnce(::testing::Return(fmt::format("{}",
            R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
            "Es war eine falsche Nummer, die es auslöste, das Telefon klingelte dreimal mitten in der Nacht."
            R"(</string>)"
        )));
    EXPECT_CALL(provider, translate(text, language_code::English, language_code::Greek))
        .WillOnce(::testing::Return(fmt::format("{}",
            R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
            "Ήταν ένας λάθος αριθμός που το ξεκίνησε, το τηλέφωνο χτύπησε τρεις φορές μέσα στη νύχτα."
            R"(</string>)"
        )));
    EXPECT_CALL(provider, translate(text, language_code::English, language_code::Spanish))
        .WillOnce(::testing::Return(fmt::format("{}",
            R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
            "Fue un número equivocado lo que lo inició, el teléfono sonó tres veces en la oscuridad de la noche."
            R"(</string>)"
        )));
    EXPECT_CALL(provider, translate(text, language_code::English, language_code::French))
        .WillOnce(::testing::Return(fmt::format("{}",
            R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
            "C’est un mauvais numéro qui l’a déclenché, le téléphone sonnant trois fois en pleine nuit."
            R"(</string>)"
        )));
    EXPECT_CALL(provider, translate(text, language_code::English, language_code::Italian))
        .WillOnce(::testing::Return(fmt::format("{}",
            R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
            "Era un numero sbagliato che lo avviava, il telefono squillava tre volte nel cuore della notte."
            R"(</string>)"
        )));
    EXPECT_CALL(provider, translate(text, language_code::English, language_code::Polish))
        .WillOnce(::testing::Return(fmt::format("{}",
            R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
            "To był zły numer, który go rozpoczął, telefon dzwonił trzy razy w środku nocy."
            R"(</string>)"
        )));
    EXPECT_CALL(provider, translate(text, language_code::English, language_code::Portuguese_Portugal))
        .WillOnce(::testing::Return(fmt::format("{}",
            R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
            "Foi um número errado que começou, o telefone tocou três vezes na calada da noite."
            R"(</string>)"
        )));
    EXPECT_CALL(provider, translate(text, language_code::English, language_code::Chinese_Simplified))
        .WillOnce(::testing::Return(fmt::format("{}",
            R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
            "这是一个错误的号码，电话在夜深人静的时候响了三声。"
            R"(</string>)"
        )));

    std::ostringstream oss{};
    tmcppc::problem_99::test_text_translation(oss, translator{ std::move(provider_up) });

    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("{}",
        "\ten: It was a wrong number that started it, the telephone ringing three times in the dead of night.\n"
        "\tar: كان رقما خاطئا هو الذي بدأه ، الهاتف يرن ثلاث مرات في جوف الليل.\n"
        "\tde: Es war eine falsche Nummer, die es auslöste, das Telefon klingelte dreimal mitten in der Nacht.\n"
        "\tel: Ήταν ένας λάθος αριθμός που το ξεκίνησε, το τηλέφωνο χτύπησε τρεις φορές μέσα στη νύχτα.\n"
        "\tes: Fue un número equivocado lo que lo inició, el teléfono sonó tres veces en la oscuridad de la noche.\n"
        "\tfr: C’est un mauvais numéro qui l’a déclenché, le téléphone sonnant trois fois en pleine nuit.\n"
        "\tit: Era un numero sbagliato che lo avviava, il telefono squillava tre volte nel cuore della notte.\n"
        "\tpl: To był zły numer, który go rozpoczął, telefon dzwonił trzy razy w środku nocy.\n"
        "\tpt-pt: Foi um número errado que começou, o telefone tocou três vezes na calada da noite.\n"
        "\tzh-Hans: 这是一个错误的号码，电话在夜深人静的时候响了三声。\n"
    )));
}
