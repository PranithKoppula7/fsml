add_subdirectory(./pybind11 pybind11)

pybind11_add_module(core fsml.cpp)

target_link_libraries(core PRIVATE fsml)
