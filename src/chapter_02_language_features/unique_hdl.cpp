#include "chapter_02_language_features/unique_hdl.h"

#ifdef _WIN32

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>


/* static */ HANDLE tmcppc::handle_traits::invalid() noexcept {
    return nullptr;
}

/* static */ void tmcppc::handle_traits::close(HANDLE hdl) noexcept {
    if (hdl != nullptr) {
        CloseHandle(hdl);
    }
}

#endif  // _WIN32
