target_sources(
  fsml PRIVATE 
  tensor.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
