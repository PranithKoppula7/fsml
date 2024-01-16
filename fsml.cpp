#include <pybind11/pybind11.h>

namespace py = pybind11;

float add(float arg1, float arg2) {
  return arg1 + arg2;
}

PYBIND11_MODULE(fsml, handle) {
  handle.doc() = "fsml is a full stack tiny implementation of modern machine learning";
  handle.def("float_add", &add);
}
