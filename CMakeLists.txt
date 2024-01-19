cmake_minimum_required(VERSION 3.27)
project(fsml)

add_library(fsml)

add_subdirectory(fsml)
add_subdirectory(python)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
