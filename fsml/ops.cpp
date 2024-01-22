#include "ops.h"
#include "../fsml/backend/hello.cuh"

float add(float a, float b) {
  Hello::hello_world();
  return a + b;
}
