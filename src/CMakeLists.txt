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
    GIT_TAG "4c7359fabf9bcb3d755742d015f02bef69276fc8"
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
add_subdirectory(chapter_05_date_and_time)
add_subdirectory(chapter_06_algorithms_and_data_structures)
add_subdirectory(chapter_07_concurrency)
#[[
add_subdirectory(chapter_08_design_patterns)
]]


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
    ${chapter_05_sources}
    ${chapter_06_sources}
    ${chapter_07_sources}
#[[
    ${chapter_08_sources}
]]
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
