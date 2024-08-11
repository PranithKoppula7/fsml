#include <vector>
#include "../tensor.h"

/*
* Interface to represent broadcasting 
*/
class broadcasting {
public:

    /**
     * Returns the tensors with their strides adjusted
     * to match the broadcasted shape
     */
    std::vector<tensor> broadcast(std::vector<tensor> vectors);

};