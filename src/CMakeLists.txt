set(include_dir ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(headers ${include_dir}/chapter_01_math/problems.h)

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG "7ffe87c0bc8e69cd38941b92c0b33ab2e5cf3c57"
)
FetchContent_Declare(
    range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG "d800a032132512a54c291ce55a2a43e0460591c7"
)
FetchContent_Declare(
    rtc
    GIT_REPOSITORY https://github.com/rturrado/rtc.git
    GIT_TAG "fee59d93759d65d6d5e8b653fb605583b47f832e"
)
FetchContent_MakeAvailable(fmt range-v3 rtc)

add_subdirectory(chapter_01_math)

#[[
add_executable(${PROJECT_NAME} main.cpp problems.h ${chapter_01_headers} ${chapter_01_sources})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} fmt range-v3 rtc)
]]

add_library(lib_${PROJECT_NAME} ${headers} ${chapter_01_sources})
target_include_directories(
    lib_${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(lib_${PROJECT_NAME} PROPERTIES OUTPUT_NAME lib_${PROJECT_NAME}-${PROJECT_VERSION})
target_compile_features(lib_${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(lib_${PROJECT_NAME} fmt range-v3 rtc)
