#include "chapter_02_language_features/unique_hdl.h"
#include "env.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <sstream>  // istringstream, ostringstream

#ifdef _WIN32
#include <windows.h>  // CreateFileW, ReadFile
#endif  // _WIN32

using namespace tmcppc::data_structures;
using handle = unique_hdl<HANDLE, handle_traits>;


TEST(unique_hdl, DISABLED_default_constructor) {
    handle hdl{};
    EXPECT_FALSE(static_cast<bool>(hdl));
    EXPECT_EQ(hdl.get(), handle_traits::invalid());
}

TEST(unique_hdl, DISABLED_handle_constructor_file_does_not_exist) {
#ifdef _WIN32
    const std::filesystem::path file_path{ "" };
    handle hdl{
        CreateFileW(
            file_path.wstring().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
    ) };
    EXPECT_FALSE(static_cast<bool>(hdl));
    EXPECT_EQ(hdl.get(), handle_traits::invalid());
#endif
}

TEST(unique_hdl, DISABLED_handle_constructor_file_exists) {
#ifdef _WIN32
    const auto file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    handle hdl{
        CreateFileW(
            file_path.wstring().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
    )};
    EXPECT_TRUE(static_cast<bool>(hdl));
    EXPECT_NE(hdl.get(), handle_traits::invalid());
#endif
}

TEST(unique_hdl, DISABLED_move_constructor_invalid_handle) {
    handle h1{};
    auto h2{ std::move(h1) };
    EXPECT_FALSE(static_cast<bool>(h1));
    EXPECT_EQ(h1.get(), handle_traits::invalid());
    EXPECT_FALSE(static_cast<bool>(h2));
    EXPECT_EQ(h2.get(), handle_traits::invalid());
}

TEST(unique_hdl, DISABLED_move_constructor_valid_file_handle) {
#ifdef _WIN32
    const auto file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    handle h1{
        CreateFileW(
            file_path.wstring().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
    )};
    EXPECT_TRUE(static_cast<bool>(h1));
    EXPECT_NE(h1.get(), handle_traits::invalid());
    auto h2{ std::move(h1) };
    EXPECT_FALSE(static_cast<bool>(h1));
    EXPECT_EQ(h1.get(), handle_traits::invalid());
    EXPECT_TRUE(static_cast<bool>(h2));
    EXPECT_NE(h2.get(), handle_traits::invalid());
#endif
}

TEST(unique_hdl, DISABLED_reset_invalid_handle_to_invalid_handle) {
    handle hdl{};
    EXPECT_FALSE(static_cast<bool>(hdl));
    EXPECT_FALSE(hdl.reset());
}

TEST(unique_hdl, DISABLED_reset_invalid_handle_to_valid_file_handle) {
#ifdef _WIN32
    const auto file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    handle hdl{};
    EXPECT_TRUE(hdl.reset(
        CreateFileW(
            file_path.wstring().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
    )));
#endif
}

TEST(unique_hdl, DISABLED_reset_valid_file_handle_to_invalid_handle) {
#ifdef _WIN32
    const auto file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    handle hdl{
        CreateFileW(
            file_path.wstring().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
    )};
    EXPECT_TRUE(static_cast<bool>(hdl));
    EXPECT_FALSE(hdl.reset());
#endif
}

TEST(unique_hdl, DISABLED_reset_valid_file_handle_to_valid_file_handle) {
#ifdef _WIN32
    const auto file_path_1{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    const auto file_path_2{ tmcppc::env::get_instance().get_resource_folder_path() / "faces.jpg" };
    handle h1{
        CreateFileW(
            file_path_1.wstring().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
    )};
    EXPECT_TRUE(static_cast<bool>(h1));
    EXPECT_TRUE(h1.reset(
        CreateFileW(
            file_path_2.wstring().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
    )));
#endif
}

TEST(unique_hdl, DISABLED_release_invalid_handle) {
    handle h1{};
    handle h2{ h1.release() };
    EXPECT_FALSE(static_cast<bool>(h1));
    EXPECT_FALSE(static_cast<bool>(h2));
}

TEST(unique_hdl, DISABLED_release_valid_file_handle) {
#ifdef _WIN32
    const auto file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    handle h1{
        CreateFileW(
            file_path.wstring().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
    )};
    handle h2{ h1.release() };
    EXPECT_FALSE(static_cast<bool>(h1));
    EXPECT_TRUE(static_cast<bool>(h2));
#endif
}
