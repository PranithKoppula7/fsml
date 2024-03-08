/**
 * Wrapper file around tensor class module for 
 * tensor binding and converts types to pybind11
**/

#include <variant>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include "../fsml/tensor.h"

namespace py = pybind11;

using TensorTypes = std::variant<py::int_, py::float_, py::array_t<float>>;

tensor create_tensor(py::array_t<float>);
// tensor create_tensor(py::list<float>);


void init_tensor(py::module_& m) {


  py::class_<tensor>(
    m, "Tensor"
  )
  .def(py::init([](TensorTypes t) {
    if (auto pv = std::get_if<py::int_>(&t); pv) {
      return tensor::tensor(1, py::cast<float>(*pv));
    } else if (auto pv = std::get_if<py::float_>(&t); pv) {
      return tensor::tensor(1, py::cast<float>(*pv));
    } else if (auto pv = std::get_if<py::array_t<float>>(&t); pv) {
      return create_tensor(py::cast<py::array_t<float>>(*pv));
    }
  }))
  .def("backward", &tensor::backward)
  .def("__add__", [](tensor& a, tensor& b) {
    return a + b;
  })
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