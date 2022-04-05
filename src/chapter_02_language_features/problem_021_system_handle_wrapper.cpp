#include "chapter_02_language_features/problem_021_system_handle_wrapper.h"
#include "chapter_02_language_features/unique_hdl.h"

#include <cassert>  // assert
#include <iostream>  // cout
#include <filesystem>
#include <vector>
#include <stdexcept>  // runtime_error

#include <windows.h>  // CreateFileW


void function_that_throws() { throw std::runtime_error{"I'm a throwing function!\n"}; }


void test_unique_hdl()
{
    auto file_path{ std::filesystem::current_path() / "res" / "sample.txt" };

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

    if (!file_hdl)
    {
        std::wcout << L"Error " << GetLastError() << ": in unique_hdl constructor\n";
        return;
    }
    std::wcout << L"Opened: " << file_path << L"\n";

    auto another_file_hdl{ std::move(file_hdl) };
    assert(another_file_hdl and another_file_hdl.get());

    std::vector<char> buffer(1024);
    DWORD bytesRead = 0;
    if (!ReadFile(
            another_file_hdl.get(),
            buffer.data(),
            static_cast<DWORD>(buffer.size()),
            &bytesRead,
            nullptr)
        )
    {
        std::cout << "Error " << GetLastError() << ": in ReadFile\n";
    }
    else
    {
        std::cout << "Read " << bytesRead << " from file\n";
    }

    function_that_throws();
}


// System handle wrapper
//
// Consider an operating system handle, such as a file handle.
// Write a wrapper that handles the acquisition and release of the handle,
// as well as other operations such as verifying the validity of the handle
// and moving handle ownership from one object to another.
void problem_21_main()
{
    try {
        test_unique_hdl();
    }
    catch (const std::runtime_error& ex) {
        std::cout << "Error: " << ex.what();
    }
    std::cout << "\n";
}
