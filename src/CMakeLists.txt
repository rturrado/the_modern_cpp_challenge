set(include_dir ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})


# Packages
include(FetchContent)
FetchContent_Declare(asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG "147f7225a96d45a2807a64e443177f621844e51c"
)
FetchContent_Declare(cryptopp-cmake
    GIT_REPOSITORY https://github.com/rturrado/cryptopp-cmake.git
    GIT_TAG "5c2a51ef07e4b351d967f5bb22fcf380eff9d52b"
)
FetchContent_Declare(curlcpp
    GIT_REPOSITORY https://github.com/rturrado/curlcpp.git
    GIT_TAG "e18bffcc23bca3a405c47f892b7f0c0cb9a49a26"
)
FetchContent_Declare(date
    GIT_REPOSITORY https://github.com/HowardHinnant/date.git
    GIT_TAG "22ceabf205d8d678710a43154da5a06b701c5830"
)
FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG "a33701196adfad74917046096bf5a2aa0ab0bb50"
)
FetchContent_Declare(nlohmann-json
    URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)
FetchContent_Declare(PDF-Writer
    GIT_REPOSITORY https://github.com/rturrado/PDF-Writer.git
    GIT_TAG "84aec314414a137227f768042b94c86c3bfa389e"
)
FetchContent_Declare(PNGwriter
    GIT_REPOSITORY https://github.com/rturrado/pngwriter.git
    GIT_TAG "ccaf07f8dfbb4a9fdffd418c3ccb04837a8f7f50"
)
FetchContent_Declare(pugixml
    GIT_REPOSITORY https://github.com/rturrado/pugixml.git
    GIT_TAG "bc6e2f2cdd82e74b8a99ecca4eb174e9afb0f123"
)
FetchContent_Declare(range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG "0fa54d7de5dc00655e38a08e87cda61f7aa6d5b9"
)
FetchContent_Declare(rtc
    GIT_REPOSITORY https://github.com/rturrado/rtc.git
    GIT_TAG "35eb8fdf5c3382c2ddeb887b962db0b080cec1a8"
)
FetchContent_Declare(SQLite3
    GIT_REPOSITORY https://github.com/algoritnl/sqlite-amalgamation.git
    GIT_TAG "a7b66b8f24f755317d4e4313ab906d2e70b9b536"
)
FetchContent_Declare(SqliteModernCpp
    GIT_REPOSITORY https://github.com/SqliteModernCpp/sqlite_modern_cpp.git
    GIT_TAG "34f9b076348d731e0f952a8ff264a26230ce287b"
    SOURCE_SUBDIR "hdr"
)
FetchContent_Declare(ZipLib
    GIT_REPOSITORY https://github.com/rturrado/ZipLib.git
    GIT_TAG "f8d9ffb59ad6b470033e5c4a0e11a681fde797fe"
)
FetchContent_MakeAvailable(
    asio
    cryptopp-cmake
    curlcpp
    date
    fmt
    nlohmann-json
    PDF-Writer
    PNGwriter
    pugixml
    range-v3
    rtc
    SQLite3
    SqliteModernCpp
    ZipLib
)
find_package(Boost 1.78.0 REQUIRED)
find_package(Threads REQUIRED)


# Subdirectories
# One per book's chapter
add_subdirectory(chapter_01_math)
add_subdirectory(chapter_02_language_features)
add_subdirectory(chapter_03_strings_and_regular_expressions)
add_subdirectory(chapter_04_streams_and_filesystems)
add_subdirectory(chapter_05_date_and_time)
add_subdirectory(chapter_06_algorithms_and_data_structures)
add_subdirectory(chapter_07_concurrency)
add_subdirectory(chapter_08_design_patterns)
add_subdirectory(chapter_09_data_serialization)
add_subdirectory(chapter_10_archives_images_and_databases)
add_subdirectory(chapter_11_cryptography)
add_subdirectory(chapter_12_networking_and_services)


# Sources
set(lib_sources
    ${chapter_01_sources}
    ${chapter_02_sources}
    ${chapter_03_sources}
    ${chapter_04_sources}
    ${chapter_05_sources}
    ${chapter_06_sources}
    ${chapter_07_sources}
    ${chapter_08_sources}
    ${chapter_09_sources}
    ${chapter_10_sources}
    ${chapter_11_sources}
    ${chapter_12_sources}
)
set(app_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problems.h"
)
list(APPEND app_sources ${lib_sources})


# asio library
add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
target_link_libraries(asio INTERFACE Threads::Threads)


# Main library
add_library(lib_${PROJECT_NAME} ${lib_sources})
target_include_directories(lib_${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_include_directories(lib_${PROJECT_NAME} SYSTEM PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${cryptopp_BINARY_DIR}
    ${curlcpp_SOURCE_DIR}/include
    ${PDFHUMMUS_SOURCE_DIR}
    ${pngwriter_SOURCE_DIR}/src
    ${pugixml_SOURCE_DIR}/src
    ${sqlite3_SOURCE_DIR}
    ${sqlitemoderncpp_SOURCE_DIR}/hdr
    ${ziplib_SOURCE_DIR}
)
message(STATUS
    "[${PROJECT_NAME}] Target include directories:\n"
    "      cryptopp: ${cryptopp_BINARY_DIR}\n"
    "      curlcpp: ${curlcpp_SOURCE_DIR}/include\n"
    "      PDF-Writer: ${PDFHUMMUS_SOURCE_DIR}\n"
    "      PNGwriter: ${pngwriter_SOURCE_DIR}/src\n"
    "      pugixml ${pugixml_SOURCE_DIR}/src\n"
    "      SQLite3: ${sqlite3_SOURCE_DIR}\n"
    "      SqliteModernCpp: ${sqlitemoderncpp_SOURCE_DIR}/hdr\n"
    "      ZipLib: ${ziplib_SOURCE_DIR}"
)
set_target_properties(lib_${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION}
)
target_compile_features(lib_${PROJECT_NAME} PRIVATE cxx_std_23)
# PDFWriter (which uses zlib.lib) has link conflicts with curlcpp (which uses libcurl.dll, which uses zlib1.dll)
# Linking PDFWriter as public and curlcpp as private avoids those conflicts
target_link_libraries(lib_${PROJECT_NAME} PUBLIC
    asio
    cryptopp-static
    date
    date-tz
    fmt
    nlohmann_json::nlohmann_json
    range-v3
    rtc
    PDFWriter
    PNGwriter
    pugixml::pugixml
    SQLite3
    ZIPLIB
)
target_link_libraries(lib_${PROJECT_NAME} PRIVATE
    curlcpp::curlcpp
)
if(CODE_COVERAGE)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        target_compile_options(lib_${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
        target_link_libraries(lib_${PROJECT_NAME} PRIVATE gcov)
        target_link_options(lib_${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
    endif()
endif()


# Main executable
add_executable(${PROJECT_NAME} ${app_sources})
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE lib_${PROJECT_NAME})


# Target compile options
if(MSVC)
    set(msvc_compile_options
        /W3 /WX /w34996
        /D_CONSOLE /DCONSOLE
        /D_UNICODE /DUNICODE
        /diagnostics:column /EHsc /FC /fp:precise /Gd /GS /sdl /utf-8 /Zc:inline
    )
    target_compile_options(lib_${PROJECT_NAME} PRIVATE ${msvc_compile_options})
    target_compile_options(${PROJECT_NAME} PRIVATE ${msvc_compile_options})
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(unixlike_compile_options
        -pedantic-errors -Werror -Wall -Wextra
        -Wl,-z,defs
        -Wno-deprecated
        # -Wconversion -Wsign-conversion -Wno-sign-conversion  # do not sort flags; order matters
    )
    target_compile_options(lib_${PROJECT_NAME} PRIVATE ${unixlike_compile_options})
    target_compile_options(${PROJECT_NAME} PRIVATE ${unixlike_compile_options})
endif()
if(CODE_COVERAGE)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
        target_link_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
    endif()
endif()
