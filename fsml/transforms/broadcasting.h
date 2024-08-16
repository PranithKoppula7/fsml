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


    /** 
     * pads dimensions with 1 from left to right
     * 
     * @param shapes 2d vector of type `int` (shapes of tensors to pad)
     * @return 2d vector of `int`, shapes padded with 1
    */
    std::vector<std::vector<int>> pad_left(
        std::vector<std::vector<int>> shapes);
    
    /**
     * returns the broadcast shape by finding max dimension for each dimension
     * 
     * @param shapes 2d vector of type `int` 
     * @return vector of `int` represnting the broadcast shape to be done
    */
    std::vector<int> broadcast_shape(
        std::vector<std::vector<int>> shapes);

    tensor broadcast(tensor& a, std::vector<int> shape);
};