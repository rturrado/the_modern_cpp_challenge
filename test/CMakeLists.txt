# Packages
include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG "af29db7ec28d6df1c7f0f745186884091e602e07"
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(Boost 1.78.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


# Subdirectories
add_subdirectory(chapter_01_math)
add_subdirectory(chapter_02_language_features)
add_subdirectory(chapter_03_strings_and_regular_expressions)
add_subdirectory(chapter_04_streams_and_filesystems)
add_subdirectory(chapter_05_date_and_time)
add_subdirectory(chapter_06_algorithms_and_data_structures)
add_subdirectory(chapter_07_concurrency)
add_subdirectory(chapter_08_design_patterns)


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
)


# Test executable
add_executable(${PROJECT_NAME}_test ${test_sources})
target_compile_features(${PROJECT_NAME}_test PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME}_test lib_${PROJECT_NAME} gmock gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)


# Resource dir
# Create a symbolic link from <source dir>/res to <test binary dir>/res
add_custom_target(resources_test)
set(resources_source_dir "${CMAKE_SOURCE_DIR}/res")
set(resources_destination_dir "${CMAKE_CURRENT_BINARY_DIR}/res")
cmake_path(NATIVE_PATH resources_source_dir NORMALIZE resources_native_source_dir)
cmake_path(NATIVE_PATH resources_destination_dir NORMALIZE resources_native_destination_dir)
add_custom_command(
    TARGET resources_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${resources_native_source_dir} ${resources_native_destination_dir}
    DEPENDS ${resources_native_destination_dir}
    COMMENT "symbolic link resources folder from ${resources_native_source_dir} to ${resources_native_destination_dir}"
)
add_dependencies(${PROJECT_NAME}_test resources_test)
