include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG "af29db7ec28d6df1c7f0f745186884091e602e07"
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(chapter_01_math)

add_executable(${PROJECT_NAME}_test ${chapter_01_test_sources})
target_compile_features(${PROJECT_NAME}_test PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME}_test lib_${PROJECT_NAME} gmock gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
