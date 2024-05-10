enable_testing()

add_executable(fsml_test tensor_test.cpp buffer_test.cpp)
target_link_libraries(fsml_test fsml GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(fsml_test)
