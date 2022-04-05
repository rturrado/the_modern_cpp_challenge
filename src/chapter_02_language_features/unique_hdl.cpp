#include "chapter_02_language_features/unique_hdl.h"

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>


/* static */ HANDLE handle_traits::invalid() noexcept
{
    return nullptr;
}

/* static */ void handle_traits::close(HANDLE hdl) noexcept
{
    if (hdl != nullptr)
    {
        CloseHandle(hdl);
    }
}