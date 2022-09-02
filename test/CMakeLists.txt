# Packages
include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG "61720589cbef9707b3c5247d02141a7c31e2876f"
)
FetchContent_Declare(perceptualdiff
    GIT_REPOSITORY https://github.com/rturrado/perceptualdiff.git
    GIT_TAG "5aa1de51b33f05b9e6318c7a961a865ddb61d602"
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(
    googletest
    perceptualdiff
)
find_package(Boost 1.78.0 REQUIRED)


# Subdirectories
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


# Test sources
set(test_sources
    ${chapter_01_test_sources}
    ${chapter_02_test_sources}
    ${chapter_03_test_sources}
    ${chapter_04_test_sources}
    ${chapter_05_test_sources}
    ${chapter_06_test_sources}
    ${chapter_07_test_sources}
    ${chapter_08_test_sources}
    ${chapter_09_test_sources}
    ${chapter_10_test_sources}
    ${chapter_11_test_sources}
    ${chapter_12_test_sources}
)
set(app_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)
list(APPEND app_sources ${test_sources})


# Test executable
add_executable(${PROJECT_NAME}_test ${app_sources})
target_include_directories(${PROJECT_NAME}_test PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${perceptualdiff_SOURCE_DIR}
)
message(STATUS
    "[${PROJECT_NAME}_test] Target include directories:\n"
    "      perceptualdiff: ${perceptualdiff_SOURCE_DIR}\n"
)
target_compile_features(${PROJECT_NAME}_test PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME}_test PUBLIC
    lib_${PROJECT_NAME}
    gmock
    gtest
    pdiff
)
if(MSVC OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC"))
    target_compile_options(${PROJECT_NAME}_test PRIVATE  /D_CONSOLE /DCONSOLE /D_UNICODE /DUNICODE /diagnostics:column /EHsc /FC /fp:precise /Gd /GS /sdl /W3 /WX /w34996 /utf-8 /Zc:inline)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME}_test PRIVATE -pedantic-errors -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
endif()


# Copy DLLs the target depends on
add_custom_command(
    TARGET ${PROJECT_NAME}_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}_test> $<TARGET_FILE_DIR:${PROJECT_NAME}_test>
    COMMAND_EXPAND_LISTS
)


include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
