#include "chapter_02_language_features/unique_hdl.h"

#ifdef _WIN32

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>


namespace tmcppc::data_structures {
    /* static */ HANDLE handle_traits::invalid() noexcept {
        return nullptr;
    }

    /* static */ void handle_traits::close(HANDLE hdl) noexcept {
        if (hdl != nullptr) {
            CloseHandle(hdl);
        }
    }
}  // namespace tmcppc::data_structures


#endif  // _WIN32
