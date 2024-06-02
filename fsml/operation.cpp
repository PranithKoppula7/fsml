#include "../fsml/backend/tensor.cuh"

#include "operation.h"
#include "tensor.h"
#include "buffer.h"

tensor add::forward(tensor& x, tensor& y) {
    float* c = Tensor::tensor_add(x.size(), x.data(), y.data());
    std::vector<float> b;
    for (int i = 0; i < x.size(); i++) {
        b.push_back(c[i]);
    }
    tensor t = tensor(b, x.shape());
    t.ctx_ = this;
    return t;
}

void add::backward(tensor& t) {
    if (t.size() < 2) return;

    tensor* p1 = t.parents_.at(0);
    tensor* p2 = t.parents_.at(1);

    p1->grad = new tensor(std::vector<float>(p1->size(), 1.0), std::vector<int>{p1->size()});
    p2->grad = new tensor(std::vector<float>(p2->size(), 1.0), std::vector<int>{p2->size()});

    return;
}

// tensor reshape::forward(tensor& x, std::vector<int> shape) {
//     int shape_total = 1;
//     for (int s: shape) shape_total *= s;

//     if (shape_total != x.size()) {
//         std::string shape_str = "";
//         for (int i = 0; i < shape.size(); i++) {
//             shape_str += std::to_string(shape[i]);
//             if (i != shape.size() - 1) {
//                 shape_str += ",";
//             }
//         }
//         throw std::runtime_error(
//             "cannot reshape tensor of size " 
//              + std::to_string(x.size())
//              + "into shape "
//              + "(" + shape_str + ")"
//         );
//     }

//     input_shape = x.shape();
//     return tensor(x.size(), x.data(), shape);
// }
