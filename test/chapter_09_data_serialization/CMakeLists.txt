# Subdirectories
add_subdirectory(json)
add_subdirectory(pdf)
add_subdirectory(xml)


set(chapter_09_test_sources
    ${chapter_09_test_json_sources}
    ${chapter_09_test_pdf_sources}
    ${chapter_09_test_xml_sources}
    "${CMAKE_CURRENT_SOURCE_DIR}/movies.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_073_xml_serialization.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_074_using_xpath.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_075_json_serialization.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_076_json_deserialization.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_077_printing_a_list_of_movies_to_a_pdf.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_078_creating_a_pdf_from_a_collection_of_images.cpp"
    PARENT_SCOPE
)
