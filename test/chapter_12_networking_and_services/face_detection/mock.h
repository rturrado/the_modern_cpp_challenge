#pragma once

#include "chapter_12_networking_and_services/face_detection.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>


namespace tmcppc::face_detection {
    struct provider_mock : public provider_adaptor {
        MOCK_METHOD((provider_response), detect, (const std::filesystem::path& path), (const, override));
    };
}  // namespace tmcppc::face_detection
