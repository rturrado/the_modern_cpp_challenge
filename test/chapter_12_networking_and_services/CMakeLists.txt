# Subdirectories
add_subdirectory(bitcoin)
add_subdirectory(imap)
add_subdirectory(json)


set(chapter_12_test_sources
    ${chapter_12_test_bitcoin_sources}
    ${chapter_12_test_imap_sources}
    ${chapter_12_test_json_sources}
    "${CMAKE_CURRENT_SOURCE_DIR}/bitcoin.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/face_detection.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/faces.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fizz_buzz.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_095_finding_the_ip_address_of_a_host.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_096_fizz_buzz_client_server_application.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_097_bitcoin_exchange_rates.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_098_fetching_emails_using_imap.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_099_translating_text.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/problem_100_detecting_faces_in_a_picture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/text_translation.cpp"
    PARENT_SCOPE
)
