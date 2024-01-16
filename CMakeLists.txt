cmake_minimum_required(VERSION 3.27)

project(fsml)
add_subdirectory(pybind11)
pybind11_add_module(fsml fsml.cpp)

add_executable(main main.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
