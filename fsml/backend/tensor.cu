#include "tensor.cuh"
#include <cstddef>
#include <cstdio>
#include <cuda_device_runtime_api.h>
#include <vector_types.h>

__global__ void tensorAdd(float* a, float* b, float* c) {
  int i = threadIdx.x;
  c[i] = a[i] + b[i];
  return;
}


namespace Tensor {
  float* tensor_add(int size, float* a, float* b) {
    size_t nBytes = size * sizeof(float); 

    // host c 
    float* host_c = (float *)malloc(nBytes);

    // create pointers for gpu 
    float* cudaA = 0;
    float* cudaB = 0;
    float* cudaC = 0;

    // allocate memory in gpu 
    cudaMalloc(&cudaA, nBytes);
    cudaMalloc(&cudaB, nBytes);
    cudaMalloc(&cudaC, nBytes);

    // copy vectors into gpu
    cudaMemcpy(cudaA, a, nBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(cudaB, b, nBytes, cudaMemcpyHostToDevice);

    // gpu kernel method
    dim3 block (size);
    dim3 grid (size / block.x);
    tensorAdd<<<grid, block>>>(cudaA, cudaB, cudaC);

    // copy from gpu -> cpu and return
    cudaMemcpy(host_c, cudaC, nBytes, cudaMemcpyDeviceToHost);

    // free cuda memory
    cudaFree(cudaA);
    cudaFree(cudaB);
    cudaFree(cudaC);

    return host_c; 
  }
}
