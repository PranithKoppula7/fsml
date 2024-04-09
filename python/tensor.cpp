/**
 * Wrapper file around tensor class module for 
 * tensor binding and converts types to pybind11
**/

#include <variant>
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include "../fsml/tensor.h"

namespace py = pybind11;

using TensorInitTypes = std::variant<py::int_, py::float_, py::array_t<float>>;
using TensorAddTypes = std::variant<py::int_, py::float_, py::object>;

tensor create_tensor(TensorInitTypes t);
tensor add_tensor(tensor& a, TensorAddTypes b);
// TODO: @pranithkoppula - add list constructor
// tensor create_tensor(py::list<float>);


void init_tensor(py::module_& m) {


  py::class_<tensor>(
    m, "Tensor"
  )
  .def("hello", []() {
    return "Hello World!";
  })
  .def(py::init(&create_tensor))
  .def("backward", &tensor::backward)
  .def("size", &tensor::size)
  .def("data", [](tensor a) {
    float* data = a.data();
    py::list pl;
    for (int i = 0; i < a.size(); i++) {
      pl.append(data[i]);
    }
    return pl;
  })
  .def("grad", [](tensor a) {
    return *(a.grad);
  })
  .def("graph", &tensor::create_graph)
  .def("__add__", &add_tensor)
  .def("parents", [](tensor& a) {
    for (tensor* p: a.parents_) {
      std::cout << p->repr() << std::endl;
    }
  })
  .def("__repr__", [](tensor t) {
    return t.repr();
  });
}

tensor add_tensor(tensor& a, TensorAddTypes b) {
  if (auto pv = std::get_if<py::int_>(&b); pv) {
    return a + *pv;
  } else if (auto pv = std::get_if<py::float_>(&b); pv) {
    return a;
  } else if (auto pv = std::get_if<py::object>(&b); pv) {
    // TODO: @pranithkoppula - check for type, error handle
    return a + py::cast<tensor&>(*pv);
  }
  return tensor(1);
}


tensor create_tensor(TensorInitTypes t) {
  if (auto pv = std::get_if<py::int_>(&t); pv) {
    return tensor(1, py::cast<float>(*pv));
  } else if (auto pv = std::get_if<py::float_>(&t); pv) {
    return tensor(1, py::cast<float>(*pv));
  } else if (auto pv = std::get_if<py::array_t<float>>(&t); pv) {
    py::array_t<float> d = py::cast<py::array_t<float>>(*pv);
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

  return tensor(1);
}