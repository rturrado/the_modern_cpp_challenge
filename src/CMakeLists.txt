set(include_dir ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})


# Packages
find_package(Threads REQUIRED)

include(FetchContent)
#[[
FetchContent_Declare(asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG "f0a1e1c7c0387ad16358c81eb52528f190df625c"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
FetchContent_Declare(cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG "ee7f91f5566b6279aadf6d0b1aaf56b11963f527"
)
FetchContent_Declare(CryptoPP
    GIT_REPOSITORY https://github.com/weidai11/cryptopp.git
    GIT_TAG "c88e4bde0a9cb307f2be060f9e460541ca6f813a"
)
]]
FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG "7ffe87c0bc8e69cd38941b92c0b33ab2e5cf3c57"
)
FetchContent_Declare(nlohmann-json
    URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)
FetchContent_Declare(PDF-Writer
    GIT_REPOSITORY https://github.com/rturrado/PDF-Writer.git
    GIT_TAG "2fad304ca44f3ffa879d760a438167a17775e123"
)
FetchContent_Declare(PNGwriter
    GIT_REPOSITORY https://github.com/rturrado/pngwriter.git
    GIT_TAG "a25a1272dc244590708d91d59ac549e3761d9652"
)
FetchContent_Declare(pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG "363ebdde91214e456943822ddf422860af8bb54d"
)
FetchContent_Declare(range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG "d800a032132512a54c291ce55a2a43e0460591c7"
)
FetchContent_Declare(rtc
    GIT_REPOSITORY https://github.com/rturrado/rtc.git
    GIT_TAG "87e28ae39708739e958af0a8c3e96050c5a3f756"
)
FetchContent_Declare(SqliteModernCpp
    GIT_REPOSITORY https://github.com/SqliteModernCpp/sqlite_modern_cpp.git
    GIT_TAG "34f9b076348d731e0f952a8ff264a26230ce287b"
    SOURCE_SUBDIR "hdr"
)
FetchContent_Declare(sqlite
    URL https://sqlite.org/2022/sqlite-amalgamation-3380500.zip
    SOURCE_SUBDIR "sqlite-amalgamation-3380500"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
FetchContent_Declare(ZipLib
    GIT_REPOSITORY https://github.com/rturrado/ZipLib.git
    GIT_TAG "fca4077481af67a60b9230e262a704365e537b64"
)
FetchContent_MakeAvailable(
    #asio
    #cpr
    #CryptoPP
    fmt
    nlohmann-json
    PDF-Writer
    PNGwriter
    pugixml
    range-v3
    rtc
    SqliteModernCpp
    sqlite
    ZipLib
)
find_package(Boost 1.78.0 REQUIRED)


# Includes
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PDFHUMMUS_SOURCE_DIR})
include_directories(${pngwriter_SOURCE_DIR}/src)
include_directories(${pugixml_SOURCE_DIR})
include_directories(${sqlitemoderncpp_SOURCE_DIR}/hdr)
include_directories(${sqlite_SOURCE_DIR})
include_directories(${ziplib_SOURCE_DIR})
message(status " * Include directories:")
message(status "\t- PDF-Writer: " ${PDFHUMMUS_SOURCE_DIR})
message(status "\t- PNGwriter: " ${pngwriter_SOURCE_DIR}/src)
message(status "\t- pugixml " ${pugixml_SOURCE_DIR})
message(status "\t- SqliteModernCpp: " ${sqlitemoderncpp_SOURCE_DIR}/hdr)
message(status "\t- sqlite: " ${sqlite_SOURCE_DIR})
message(status "\t- ZipLib: " ${ziplib_SOURCE_DIR})


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
#[[
add_subdirectory(chapter_11_cryptography)
add_subdirectory(chapter_12_networking_and_services)
]]


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
#[[
    ${chapter_11_sources}
    ${chapter_11_sources}
]]
)
set(app_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problems.h"
)
list(APPEND app_sources ${lib_sources})


#[[
# asio library
add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
target_link_libraries(asio INTERFACE Threads::Threads)
]]


# Main library
add_library(lib_${PROJECT_NAME} ${lib_sources})
target_include_directories(lib_${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(lib_${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION}
)
target_compile_features(lib_${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(lib_${PROJECT_NAME}
    #asio
    #cryptopp-static
    #cpr::cpr
    fmt
    nlohmann_json::nlohmann_json
    PDFWriter
    PNGwriter
    pugixml::pugixml
    range-v3
    rtc
    ZIPLIB
)


# Main executable
add_executable(${PROJECT_NAME} ${app_sources})
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} lib_${PROJECT_NAME})


# Target compile options
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    if("${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
        target_compile_options(${PROJECT_NAME} PRIVATE /WX /W3 /D _CRT_SECURE_NO_WARNINGS)
        target_compile_options(lib_${PROJECT_NAME} PUBLIC /WX /W3 /D _CRT_SECURE_NO_WARNINGS)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -pedantic-errors -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
        target_compile_options(lib_${PROJECT_NAME} PUBLIC -pedantic-errors -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
    endif()
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -pedantic-errors -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
    target_compile_options(lib_${PROJECT_NAME} PUBLIC -pedantic-errors -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
elseif(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /WX /W3 /D _CRT_SECURE_NO_WARNINGS)
    target_compile_options(lib_${PROJECT_NAME} PUBLIC /WX /W3 /D _CRT_SECURE_NO_WARNINGS)
endif()


# Resource dir
# Create a symbolic link from <source dir>/res to <src binary dir>/res
add_custom_target(resources)
set(resources_source_dir "${CMAKE_SOURCE_DIR}/res")
set(resources_destination_dir "${CMAKE_CURRENT_BINARY_DIR}/res")
cmake_path(NATIVE_PATH resources_source_dir NORMALIZE resources_native_source_dir)
cmake_path(NATIVE_PATH resources_destination_dir NORMALIZE resources_native_destination_dir)
add_custom_command(
    TARGET resources POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${resources_native_source_dir} ${resources_native_destination_dir}
    DEPENDS ${resources_native_destination_dir}
    COMMENT "symbolic link resources folder from ${resources_native_source_dir} to ${resources_native_destination_dir}"
)
add_dependencies(${PROJECT_NAME} resources)


# Sample subfolder
# Create a symbolic link from <source dir>/res/sample_subfolder to <source dir>/res/sample_folder/sample_subfolder
add_custom_target(sample_subfolder)
set(sample_subfolder_source_dir "${CMAKE_SOURCE_DIR}/res/sample_subfolder")
set(sample_subfolder_destination_dir "${CMAKE_SOURCE_DIR}/res/sample_folder/sample_subfolder")
cmake_path(NATIVE_PATH sample_subfolder_source_dir NORMALIZE sample_subfolder_native_source_dir)
cmake_path(NATIVE_PATH sample_subfolder_destination_dir NORMALIZE sample_subfolder_native_destination_dir)
add_custom_command(
    TARGET sample_subfolder POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${sample_subfolder_native_source_dir} ${sample_subfolder_native_destination_dir}
    DEPENDS ${sample_subfolder_native_destination_dir}
    COMMENT "symbolic link sample_subfolder from ${sample_subfolder_native_source_dir} to ${sample_subfolder_native_destination_dir}"
)
add_dependencies(${PROJECT_NAME} sample_subfolder)
