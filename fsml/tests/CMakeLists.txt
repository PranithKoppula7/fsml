enable_testing()

add_executable(ops_test ops_test.cpp)
target_link_libraries(ops_test fsml GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(ops_test)
