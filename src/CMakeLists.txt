set(include_dir ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})


# Packages
include(FetchContent)
FetchContent_Declare(asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG "f0a1e1c7c0387ad16358c81eb52528f190df625c"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
FetchContent_Declare(cryptopp-cmake
    GIT_REPOSITORY https://github.com/rturrado/cryptopp-cmake.git
    GIT_TAG "1689327135734081fade00be1c783711276f0d23"
)
FetchContent_Declare(curlcpp
    GIT_REPOSITORY https://github.com/JosephP91/curlcpp.git
    GIT_TAG "4be41c6ed651d0e19eca10d08cb27605af117566"
)
FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG "4bb3af7a6ba4330284fb490b0f471172fda87f07"
)
FetchContent_Declare(nlohmann-json
    URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)
FetchContent_Declare(PDF-Writer
    GIT_REPOSITORY https://github.com/rturrado/PDF-Writer.git
    GIT_TAG "66fc2954fbce1e9903a8ff4b2f7fe90e1f61d36b"
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
    GIT_TAG "0fa54d7de5dc00655e38a08e87cda61f7aa6d5b9"
)
FetchContent_Declare(rtc
    GIT_REPOSITORY https://github.com/rturrado/rtc.git
    GIT_TAG "e82da7dbf57ebe3356c78495af3980ca056f7865"
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
    GIT_TAG "606ec487b6f6050db5bb5b195514f393928eebe8"
)
FetchContent_MakeAvailable(
    asio
    cryptopp-cmake
    curlcpp
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
target_include_directories(lib_${PROJECT_NAME} PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${cryptopp_BINARY_DIR}
    ${curlcpp_SOURCE_DIR}/include
    ${PDFHUMMUS_SOURCE_DIR}
    ${pngwriter_SOURCE_DIR}/src
    ${pugixml_SOURCE_DIR}/src
    ${sqlitemoderncpp_SOURCE_DIR}/hdr
    ${sqlite_SOURCE_DIR}
    ${ziplib_SOURCE_DIR}
)
message(STATUS
    "[${PROJECT_NAME}] Target include directories:\n"
    "      cryptopp: ${cryptopp_BINARY_DIR}\n"
    "      curlcpp: ${curlcpp_SOURCE_DIR}/include\n"
    "      PDF-Writer: ${PDFHUMMUS_SOURCE_DIR}\n"
    "      PNGwriter: ${pngwriter_SOURCE_DIR}/src\n"
    "      pugixml ${pugixml_SOURCE_DIR}/src\n"
    "      SqliteModernCpp: ${sqlitemoderncpp_SOURCE_DIR}/hdr\n"
    "      sqlite: ${sqlite_SOURCE_DIR}\n"
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
    fmt
    nlohmann_json::nlohmann_json
    range-v3
    rtc
    PDFWriter
    PNGwriter
    pugixml::pugixml
    ZIPLIB
)
target_link_libraries(lib_${PROJECT_NAME} PRIVATE
    curlcpp::curlcpp
)


# Main executable
add_executable(${PROJECT_NAME} ${app_sources})
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} lib_${PROJECT_NAME})


# Target compile options
if(MSVC OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC"))
    target_compile_options(lib_${PROJECT_NAME} PRIVATE /D_CONSOLE /DCONSOLE /D_UNICODE /DUNICODE /diagnostics:column /EHsc /FC /fp:precise /Gd /GS /sdl /W3 /WX /w34996 /utf-8 /Zc:inline)
    target_compile_options(${PROJECT_NAME} PRIVATE  /D_CONSOLE /DCONSOLE /D_UNICODE /DUNICODE /diagnostics:column /EHsc /FC /fp:precise /Gd /GS /sdl /W3 /WX /w34996 /utf-8 /Zc:inline)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(lib_${PROJECT_NAME} PRIVATE -pedantic-errors -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
    target_compile_options(${PROJECT_NAME} PRIVATE -pedantic-errors -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
endif()


# Link to sample_subfolder
# Create a symbolic link from <source dir>/res/sample_folder/sample_subfolder to <source dir>/res/sample_subfolder
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
