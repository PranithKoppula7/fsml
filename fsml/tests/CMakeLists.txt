enable_testing()

add_executable(tensor_test tensor_test.cpp)
target_link_libraries(tensor_test fsml GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tensor_test)
