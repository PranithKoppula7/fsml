#include <pybind11/pybind11.h>
#include "fsml/opps.h"


namespace py = pybind11;

PYBIND11_MODULE(fsml, handle) {
  handle.doc() = "fsml is a full stack tiny implementation of modern machine learning";
  handle.def("float_add", &add);
}
