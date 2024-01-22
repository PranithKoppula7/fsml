cmake_minimum_required(VERSION 3.27)
project(fsml LANGUAGES CXX CUDA)
enable_language(CUDA)

add_library(fsml)

add_subdirectory(fsml)
add_subdirectory(python)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
