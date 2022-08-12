# Subdirectories
add_subdirectory(v1)
add_subdirectory(v2)


set(chapter_02_test_temperature_sources
    ${chapter_02_test_temperature_v1_sources}
    ${chapter_02_test_temperature_v2_sources}
    PARENT_SCOPE
)
