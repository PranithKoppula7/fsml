#include <pybind11/pybind11.h>

namespace py = pybind11;


PYBIND11_MODULE(core, handle) {
  handle.doc() = "fsml is a full stack tiny implementation of modern machine learning";
}
