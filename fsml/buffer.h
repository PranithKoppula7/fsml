#include <vector>
#include <cstddef>
#include <cstdint>
#include <memory>

template <typename T>
class buffer {

public:
    buffer(std::vector<int>& shape);

private:
    std::vector<int> shape;
    std::vector<std::size_t> strides;
    std::size_t size;
    std::unique_ptr<T*> data;


};