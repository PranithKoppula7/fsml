#include <pybind11/pybind11.h>
#include "../fsml/tensor.h"

namespace py = pybind11;


PYBIND11_MODULE(core, handle) {
  handle.doc() = "fsml is a full stack tiny implementation of modern machine learning";
  py::class_<tensor::tensor>(
    handle, "Tensor"
  )
  .def(py::init<int>())
  .def(py::init<int, float>());
}
