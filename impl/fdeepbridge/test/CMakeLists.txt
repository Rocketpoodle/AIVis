set(TEST_NAME tst-annrepresentation)

find_package(Qt6 6.5 REQUIRED COMPONENTS Test)
find_package(frugally-deep)
find_package(eigen)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_image_classifier.json
    ${CMAKE_CURRENT_BINARY_DIR}/simple_image_classifier.json
    COPYONLY
)

add_executable(${TEST_NAME}
        "tst_annrepresentation.cpp"
)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} -o test_messages.xml -xunitxml)
target_link_libraries(${TEST_NAME} PRIVATE Qt::Test frugally-deep::fdeep Eigen3::Eigen fdeepbridge)
