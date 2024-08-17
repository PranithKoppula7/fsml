target_sources(
  fsml
  PUBLIC
  tensor.cu
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/codegen)