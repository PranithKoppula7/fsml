target_sources(
  fsml PUBLIC 
  tensor.cpp
  operation.cpp
)

# --- graphviz --- #
include_directories("/usr/include/graphviz")
add_executable(graph graph.cpp)
target_link_libraries(graph PUBLIC cgraph gvc)
add_custom_command(TARGET graph POST_BUILD COMMAND graph)
# ---------------- #

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
