/**
 * Wrapper file around tensor class module for 
 * tensor binding and converts types to pybind11
**/


#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "../fsml/tensor.h"

namespace py = pybind11;

tensor create_tensor(py::array_t<float>);
// tensor create_tensor(py::list<float>);

void init_tensor(py::module_& m) {
  py::class_<tensor>(
    m, "Tensor"
  )
  .def(py::init<int>())
  .def(py::init<int, float>())
  .def(py::init([](py::array_t<float> d) {
    return create_tensor(d);
  }))
  .def("__repr__", [](tensor t) {
    return t.repr();
  });
}


tensor create_tensor(py::array_t<float> d) {
  py::buffer_info d_buffer = d.request();
  std::vector<py::ssize_t> shape = d_buffer.shape;

  std::vector<int> shape_vec;
  int size = 1;

  for (py::ssize_t s: shape) {
    shape_vec.push_back((int) s);
    size *= (int)s;
  }

  return tensor(size, 
                static_cast<float*>(d_buffer.ptr),
                shape_vec);
}