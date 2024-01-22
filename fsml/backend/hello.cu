#include <cuda_runtime_api.h>
#include <stdio.h>
#include "hello.cuh"

__global__ void helloFromGPU(void) {
  printf("Hello World from GPU!\n");
}

namespace Hello {
  void hello_world() {
    helloFromGPU<<<1, 1>>>();
    cudaDeviceReset();
  }
}
