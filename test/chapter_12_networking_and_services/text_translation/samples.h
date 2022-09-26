#pragma once

#include "fmt/format.h"

#include <string>


namespace tmcppc::text_translation::samples::provider_response_text {
    static inline const std::string error{
        R"(<html><body><h1>Argument Exception</h1>)"
        R"(<p>Method: Translate()</p>)"
        R"(<p>Parameter: </p><p>Message: Invalid Azure Subscription key.</p>)"
        R"(<code></code>)"
        R"(<p>message id=V2_Rest_Translate.BNZE.1C19.0730T1725.B03984</p></body></html>)"
    };
    static inline const std::string arabic{ fmt::format("{}",
        R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
        "كان رقما خاطئا هو الذي بدأه ، الهاتف يرن ثلاث مرات في جوف الليل."
        R"(</string>)"
    ) };
    static inline const std::string german{ fmt::format("{}",
        R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
        "Es war eine falsche Nummer, die es auslöste, das Telefon klingelte dreimal mitten in der Nacht."
        R"(</string>)"
    ) };
    static inline const std::string greek{ fmt::format("{}",
        R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
        "Ήταν ένας λάθος αριθμός που το ξεκίνησε, το τηλέφωνο χτύπησε τρεις φορές μέσα στη νύχτα."
        R"(</string>)"
    ) };
    static inline const std::string spanish{ fmt::format("{}",
        R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
        "Fue un número equivocado lo que lo inició, el teléfono sonó tres veces en la oscuridad de la noche."
        R"(</string>)"
    ) };
    static inline const std::string french{ fmt::format("{}",
        R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
        "C’est un mauvais numéro qui l’a déclenché, le téléphone sonnant trois fois en pleine nuit."
        R"(</string>)"
    ) };
    static inline const std::string italian{ fmt::format("{}",
        R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
        "Era un numero sbagliato che lo avviava, il telefono squillava tre volte nel cuore della notte."
        R"(</string>)"
    ) };
    static inline const std::string polish{ fmt::format("{}",
        R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
        "To był zły numer, który go rozpoczął, telefon dzwonił trzy razy w środku nocy."
        R"(</string>)"
    ) };
    static inline const std::string portuguese_portugal{ fmt::format("{}",
        R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
        "Foi um número errado que começou, o telefone tocou três vezes na calada da noite."
        R"(</string>)"
    ) };
    static inline const std::string chinese_simplified{ fmt::format("{}",
        R"(<string xmlns="http://schemas.microsoft.com/2003/10/Serialization/">)"
        "这是一个错误的号码，电话在夜深人静的时候响了三声。"
        R"(</string>)"
    ) };
}  // tmcppc::text_translation::samples::provider_response_text
