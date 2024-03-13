set(TEST_NAME tst-interface)

find_package(Qt6 6.5 REQUIRED COMPONENTS Test)

add_executable(${TEST_NAME}
        "tst_interface.cpp"
)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} -o test_messages.xml -xunitxml)
target_link_libraries(${TEST_NAME} PRIVATE Qt::Test)
