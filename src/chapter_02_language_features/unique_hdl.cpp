#include "chapter_02_language_features/unique_hdl.h"

#ifdef _WIN32
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#endif  // _WIN32


namespace tmcppc::data_structures {
    /* static */ HANDLE handle_traits::invalid() noexcept {
#ifdef _WIN32
        return INVALID_HANDLE_VALUE;
#else
        return nullptr;
#endif  // _WIN32
    }

    /* static */ void handle_traits::close(HANDLE hdl) noexcept {
#ifdef _WIN32
        if (hdl != INVALID_HANDLE_VALUE) {
            CloseHandle(hdl);
#endif  // _WIN32
        }
    }
}  // namespace tmcppc::data_structures
