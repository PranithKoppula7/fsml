#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "../fsml/tensor.h"

namespace py = pybind11;

tensor::tensor create_tensor(py::array);
// tensor::tensor create_tensor(py::list<float>);

void init_tensor(py::module_& m) {
  py::class_<tensor::tensor>(
    m, "Tensor"
  )
  .def(py::init<int>())
  .def(py::init<int, float>())
  .def(py::init([](py::array d) {
    return create_tensor(d);
  }));
}


tensor::tensor create_tensor(py::array d) {
    py::print("hello!");
    return tensor::tensor(1);
}