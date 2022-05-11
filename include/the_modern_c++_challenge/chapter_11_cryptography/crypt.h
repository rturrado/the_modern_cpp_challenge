#ifndef CRYPT_H
#define CRYPT_H

#include <string>

class Crypt
{
public:
    virtual ~Crypt() = default;

    [[nodiscard]] virtual std::string encrypt(std::string_view text) const = 0;
    [[nodiscard]] virtual std::string decrypt(std::string_view text) const = 0;
};

#endif CRYPT_H
