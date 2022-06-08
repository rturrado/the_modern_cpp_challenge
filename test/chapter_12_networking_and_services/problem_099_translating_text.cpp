#include "chapter_12_networking_and_services/text_translation.h"
#include "chapter_12_networking_and_services/problem_099_translating_text.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>
#include <sstream>  // ostringstream
#include <string_view>

using namespace tmcppc::text_translation;


namespace tmcppc::text_translation {
    class translator_mock : public translator_adaptor {
    public:
        // Translation is done from utf8 to utf8
        MOCK_METHOD(std::string, translate,
            (std::string_view text, language_code from, language_code to), (const, override));
    };
}  // namespace tmcppc::text_translation


TEST(test_text_translation, DISABLED_output) {
    std::string_view text{ "It was a wrong number that started it, the telephone ringing three times in the dead of night." };
    translator_mock translator{};
    EXPECT_CALL(translator, translate(text, language_code::English, language_code::Arabic))
        .WillOnce(::testing::Return(fmt::format("{}",
            "كان رقما خاطئا هو الذي بدأه ، الهاتف يرن ثلاث مرات في جوف الليل.")));
    EXPECT_CALL(translator, translate(text, language_code::English, language_code::German))
        .WillOnce(::testing::Return(fmt::format("{}",
            "Es war eine falsche Nummer, die es auslöste, das Telefon klingelte dreimal mitten in der Nacht.")));
    EXPECT_CALL(translator, translate(text, language_code::English, language_code::Greek))
        .WillOnce(::testing::Return(fmt::format("{}",
            "Ήταν ένας λάθος αριθμός που το ξεκίνησε, το τηλέφωνο χτύπησε τρεις φορές μέσα στη νύχτα.")));
    EXPECT_CALL(translator, translate(text, language_code::English, language_code::Spanish))
        .WillOnce(::testing::Return(fmt::format("{}",
            "Fue un número equivocado lo que lo inició, el teléfono sonó tres veces en la oscuridad de la noche.")));
    EXPECT_CALL(translator, translate(text, language_code::English, language_code::French))
        .WillOnce(::testing::Return(fmt::format("{}",
            "C’est un mauvais numéro qui l’a déclenché, le téléphone sonnant trois fois en pleine nuit.")));
    EXPECT_CALL(translator, translate(text, language_code::English, language_code::Italian))
        .WillOnce(::testing::Return(fmt::format("{}",
            "Era un numero sbagliato che lo avviava, il telefono squillava tre volte nel cuore della notte.")));
    EXPECT_CALL(translator, translate(text, language_code::English, language_code::Polish))
        .WillOnce(::testing::Return(fmt::format("{}",
            "To był zły numer, który go rozpoczął, telefon dzwonił trzy razy w środku nocy.")));
    EXPECT_CALL(translator, translate(text, language_code::English, language_code::Portuguese_Portugal))
        .WillOnce(::testing::Return(fmt::format("{}",
            "Foi um número errado que começou, o telefone tocou três vezes na calada da noite.")));
    EXPECT_CALL(translator, translate(text, language_code::English, language_code::Chinese_Simplified))
        .WillOnce(::testing::Return(fmt::format("{}",
            "这是一个错误的号码，电话在夜深人静的时候响了三声。")));

    std::ostringstream oss{};
    test_text_translation(oss, &translator);

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
