cmake_minimum_required(VERSION 3.27)

project(fsml)

add_subdirectory(pybind11)

add_library(fsml fsml/ops.cpp)

add_subdirectory(python)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
