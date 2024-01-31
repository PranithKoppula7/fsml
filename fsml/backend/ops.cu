#include "ops.cuh"
#include <cstdio>

__global__ void tensorAdd(const float* a, const float* b, float* c) {
  printf("Hello World from GPU!\n");
  int i = threadIdx.x;
  c[i] = a[i] + b[i];
  return;
}


namespace Ops {
  float* tensor_add(float* a, float* b) {
    float c[sizeof(a) / sizeof(float)] = { 0 };

    // create pointers for gpu 
    float* cudaA = 0;
    float* cudaB = 0;
    float* cudaC = 0;

    // allocate memory in gpu 
    cudaMalloc(&cudaA, sizeof(a));
    cudaMalloc(&cudaB, sizeof(b));
    cudaMalloc(&cudaC, sizeof(c));

    // copy vectors into gpu
    cudaMemcpy(cudaA, a, sizeof(a), cudaMemcpyHostToDevice);
    cudaMemcpy(cudaB, b, sizeof(b), cudaMemcpyHostToDevice);

    // gpu kernel method
    tensorAdd<<<1, sizeof(a) / sizeof(float) >>>(cudaA, cudaB, cudaC);

    // copy from gpu -> cpu and return
    float* ans = 0;
    cudaMemcpy(ans, cudaC, sizeof(cudaC), cudaMemcpyDeviceToHost);

    cudaDeviceReset();

    return ans;
  }
}
