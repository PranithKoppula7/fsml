#include "operation.h"
#include "tensor.h"
#include "../fsml/backend/tensor.cuh"

tensor add::forward(tensor x, tensor y) {
    float* c = Tensor::tensor_add(x.size(), x.data(), y.data());
    return tensor(x.size(), c);
}
