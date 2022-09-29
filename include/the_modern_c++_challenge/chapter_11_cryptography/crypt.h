#pragma once

#include <string>
#include <string_view>

class crypt {
public:
    virtual ~crypt() = default;

    [[nodiscard]] virtual std::string encrypt(std::string_view text) const = 0;
    [[nodiscard]] virtual std::string decrypt(std::string_view text) const = 0;
};
