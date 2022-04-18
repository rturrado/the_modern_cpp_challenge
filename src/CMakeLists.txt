set(include_dir ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})


# Packages
include(FetchContent)
FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG "7ffe87c0bc8e69cd38941b92c0b33ab2e5cf3c57"
)
FetchContent_Declare(range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG "d800a032132512a54c291ce55a2a43e0460591c7"
)
FetchContent_Declare(rtc
    GIT_REPOSITORY https://github.com/rturrado/rtc.git
    GIT_TAG "647097a5e52460547b4ea4b00fa267d31ef6d6e2"
)
FetchContent_MakeAvailable(fmt range-v3 rtc)

find_package(Boost 1.78.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


# Subdirectories
# One per book's chapter
add_subdirectory(chapter_01_math)
add_subdirectory(chapter_02_language_features)
add_subdirectory(chapter_03_strings_and_regular_expressions)
add_subdirectory(chapter_04_streams_and_filesystems)


# Sources
set(app_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problems.h"
)
set(lib_sources
    ${chapter_01_sources}
    ${chapter_02_sources}
    ${chapter_03_sources}
    ${chapter_04_sources}
)
list(APPEND app_sources ${lib_sources})


# Main executable
add_executable(${PROJECT_NAME} ${app_sources})
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} fmt range-v3 rtc)


# Main library
add_library(lib_${PROJECT_NAME} ${lib_sources})
target_include_directories(lib_${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(lib_${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION})
target_compile_features(lib_${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(lib_${PROJECT_NAME} fmt range-v3 rtc)


# Resource dir
# Create a symbolic link from <source dir>/res to <src binary dir>/res
add_custom_target(resources)
set(res_source_dir "${CMAKE_SOURCE_DIR}/res")
set(res_destination_dir "${CMAKE_CURRENT_BINARY_DIR}/res")
cmake_path(NATIVE_PATH res_source_dir NORMALIZE res_native_source_dir)
cmake_path(NATIVE_PATH res_destination_dir NORMALIZE res_native_destination_dir)
add_custom_command(
    TARGET resources POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${res_native_source_dir} ${res_native_destination_dir}
    DEPENDS ${res_native_destination_dir}
    COMMENT "symbolic link resources folder from ${res_native_source_dir} to ${res_native_destination_dir}"
)
add_dependencies(${PROJECT_NAME} resources)
