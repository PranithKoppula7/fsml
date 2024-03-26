target_sources(
  fsml PUBLIC 
  tensor.cpp
  operation.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
