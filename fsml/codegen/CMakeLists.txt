# --- llvm --- #
target_include_directories(fsml PUBLIC "/usr/include/llvm-18")
target_include_directories(fsml PUBLIC "/usr/include/llvm-c-18")
target_link_libraries(fsml PUBLIC LLVM)
# ---------------# 

target_sources(
  fsml PUBLIC 
  codegen.h
  codegen.cpp
)