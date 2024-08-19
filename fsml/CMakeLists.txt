target_sources(
  fsml PUBLIC 
  buffer.cpp
  tensor.cpp
  operation.cpp
  graph.cpp
)

# --- graphviz --- #
include_directories("/usr/include/graphviz")
target_link_libraries(fsml PUBLIC cgraph gvc)
# ---------------- #

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/transforms)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/codegen)

