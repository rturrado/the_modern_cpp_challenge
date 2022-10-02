#pragma once

#include <fmt/format.h>
#include <string>
#include <string_view>


namespace tmcppc::text_translation::samples {
    static inline const std::string error_output{
        "Invalid Azure Subscription key."
    };
    static inline const std::string_view english{
        "It was a wrong number that started it, the telephone ringing three times in the dead of night."
    };
    static inline const std::string arabic_output{ fmt::format("{}",
        "كان رقما خاطئا هو الذي بدأه ، الهاتف يرن ثلاث مرات في جوف الليل."
    ) };
    static inline const std::string german_output{ fmt::format("{}",
        "Es war eine falsche Nummer, die es auslöste, das Telefon klingelte dreimal mitten in der Nacht."
    ) };
    static inline const std::string greek_output{ fmt::format("{}",
        "Ήταν ένας λάθος αριθμός που το ξεκίνησε, το τηλέφωνο χτύπησε τρεις φορές μέσα στη νύχτα."
    ) };
    static inline const std::string spanish_output{ fmt::format("{}",
        "Fue un número equivocado lo que lo inició, el teléfono sonó tres veces en la oscuridad de la noche."
    ) };
    static inline const std::string french_output{ fmt::format("{}",
        "C’est un mauvais numéro qui l’a déclenché, le téléphone sonnant trois fois en pleine nuit."
    ) };
    static inline const std::string italian_output{ fmt::format("{}",
        "Era un numero sbagliato che lo avviava, il telefono squillava tre volte nel cuore della notte."
    ) };
    static inline const std::string polish_output{ fmt::format("{}",
        "To był zły numer, który go rozpoczął, telefon dzwonił trzy razy w środku nocy."
    ) };
    static inline const std::string portuguese_portugal_output{ fmt::format("{}",
        "Foi um número errado que começou, o telefone tocou três vezes na calada da noite."
    ) };
    static inline const std::string chinese_simplified_output{ fmt::format("{}",
        "这是一个错误的号码，电话在夜深人静的时候响了三声。"
    ) };
}  // tmcppc::text_translation::samples
