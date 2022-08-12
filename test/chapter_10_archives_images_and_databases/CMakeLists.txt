# Subdirectories
add_subdirectory(console)
add_subdirectory(ean_13)
add_subdirectory(file)
add_subdirectory(png)
add_subdirectory(sql)
add_subdirectory(zip)


set(chapter_10_test_sources
    ${chapter_10_test_console_sources}
    ${chapter_10_test_ean_13_sources}
    ${chapter_10_test_file_sources}
    ${chapter_10_test_png_sources}
    ${chapter_10_test_sql_sources}
    ${chapter_10_test_zip_sources}
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_079_finding_files_in_a_zip_archive.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_080_zip_compression.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_081_zip_compression_with_password.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_082_national_flag_png.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_083_verification_text_png.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_084_ean_13_barcode_generator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_085_reading_from_an_sqlite_db.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_086_inserting_into_an_sqlite_db.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_087_handling_images_in_an_sqlite_db.cpp"
    PARENT_SCOPE
)
