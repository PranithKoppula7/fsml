#include <vector>
#include <string>

class tensor;

class operation {
public:
    std::string op_;

    virtual tensor forward(tensor& x, tensor& y) = 0; 
    virtual void backward(tensor& t) = 0;

};

class add : public operation {
public:
    add() {
        op_ = "+"; 
    }
    tensor forward(tensor& x, tensor& y);
    void backward(tensor& t);
};