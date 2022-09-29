#pragma once

#include "chapter_12_networking_and_services/text_translation.h"

#include <filesystem>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>


namespace tmcppc::text_translation {
    struct provider_mock : public provider_adaptor {
        MOCK_METHOD((std::string), translate, (std::string_view text, tmcppc::text_translation::language_code from,
            tmcppc::text_translation::language_code to), (const, override));
    };
}  // namespace tmcppc::text_translation
