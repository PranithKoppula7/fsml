#include "../fsml/backend/tensor.cuh"

#include "operation.h"
#include "tensor.h"

tensor add::forward(tensor& x, tensor& y) {
    float* c = Tensor::tensor_add(x.size(), x.data(), y.data());
    tensor t = tensor(x.size(), c);
    t.ctx_ = this;
    return t;
}

void add::backward(tensor& t) {
    if (t.size() < 2) return;

    tensor* p1 = t.parents_.at(0);
    tensor* p2 = t.parents_.at(1);

    p1->grad += t.grad;
    p2->grad += t.grad;
}
