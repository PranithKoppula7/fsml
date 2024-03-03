#include "../fsml/backend/tensor.cuh"
#include "tensor.h"

#include <vector>

class operation {

public:
    operation(std::vector<tensor> parents) {
        parents_ = parents;
    }

    tensor forward(tensor x, tensor y); 
    tensor backward(tensor grad);

private:
    std::vector<tensor> parents_;
};

class add : public operation {
public:
    add() = delete;

    static tensor forward(tensor x, tensor y);
};