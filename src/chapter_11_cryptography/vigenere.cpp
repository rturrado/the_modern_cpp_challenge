#include "chapter_11_cryptography/vigenere.h"


namespace tmcppc::crypto {
    /* static */ constexpr vigenere::square_t vigenere::square_{ vigenere::build_square() };
}  // namespace tmcppc::crypto
