#include <stdio.h>

__global__ void helloFromGpu(void) {
  printf("Hello World from GPU!\n");
}

int main(void) {
  printf("Hello World from CPU!\n");
  helloFromGpu<<<1, 10>>>();
  cudaDeviceReset();
  return 0;
}
