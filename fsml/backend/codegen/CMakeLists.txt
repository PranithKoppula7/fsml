include_directories("/usr/include/llvm-18")
include_directories("/usr/include/llvm-c-18")

add_executable(codegen codegen.cpp)

target_link_libraries(codegen PUBLIC LLVM)