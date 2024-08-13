#include <vector>
#include "../tensor.h"

/*
* Interface to represent broadcasting 
*/
class broadcasting {
public:
    broadcasting(std::vector<tensor> tensors);

    /**
     * Returns the tensors with their strides adjusted
     * to match the broadcasted shape
     */
    std::vector<tensor> broadcast();

    int getSize();
    int getNdim();
    std::vector<int> getShape();
private:
    int ndim;
    int size;
    std::vector<int> shape;
    std::vector<tensor> tensors;


    std::vector<std::vector<int>> pad_left(
        std::vector<std::vector<int>> shapes);
    
    std::vector<int> broadcast_shape(
        std::vector<std::vector<int>> shapes);

    // tensor broadcast_to(
    //     tensor& x,
    //     std::vector<int> shape);

    tensor broadcast(tensor& a, std::vector<int> shape);
};