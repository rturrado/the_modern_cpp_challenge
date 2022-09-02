#include "chapter_02_language_features/problem_021_system_handle_wrapper.h"
#include "chapter_02_language_features/unique_hdl.h"
#include "env.h"

#include <cassert>  // assert
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // wcout
#include <stdexcept>  // runtime_error
#include <utility>  // move
#include <vector>

#ifdef _WIN32
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>  // CreateFileW, ReadFile
#endif  // _WIN32


void function_that_throws() {
    throw std::runtime_error{ "I'm a throwing function!" };
}


void test_unique_hdl(std::wostream& wos) {
#ifdef _WIN32
    using namespace tmcppc::data_structures;

    const auto file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };

    using handle = unique_hdl<HANDLE, handle_traits>;

    handle file_hdl{
        CreateFileW(
            file_path.wstring().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
    )};

    if (not file_hdl) {
        fmt::print(wos, L"Error in CreateFileW: {}\n", GetLastError());
        return;
    }
    fmt::print(wos, L"Opened: {}\n", file_path.generic_wstring());

    auto another_file_hdl{ std::move(file_hdl) };
    assert(another_file_hdl and another_file_hdl.get());

    std::vector<char> buffer(1024);
    DWORD bytesRead = 0;
    if (not ReadFile(
            another_file_hdl.get(),
            buffer.data(),
            static_cast<DWORD>(buffer.size()),
            &bytesRead,
            nullptr)) {
        fmt::print(wos, L"Error in ReadFile: {}\n", GetLastError());
    } else {
        fmt::print(wos, L"Read {} bytes from file\n", bytesRead);
    }

    function_that_throws();
#else
    fmt::print(wos, L"Error: Unimplemented.\n");
#endif  // _WIN32
}


void problem_21_main(std::wostream& wos) {
    try {
        test_unique_hdl(wos);
    } catch (const std::runtime_error& ex) {
        // ex.what() returns a const char*
        // Using a wostream here, instead of fmt::print, was the easiest way
        wos << L"Error: " << ex.what() << L"\n";
    }
    fmt::print(wos, L"\n");
}


// System handle wrapper
//
// Consider an operating system handle, such as a file handle.
// Write a wrapper that handles the acquisition and release of the handle,
// as well as other operations such as verifying the validity of the handle
// and moving handle ownership from one object to another.
void problem_21_main() {
    problem_21_main(std::wcout);
}
