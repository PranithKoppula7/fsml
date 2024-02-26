#include <pybind11/pybind11.h>
#include "../fsml/tensor.h"

namespace py = pybind11;

void init_tensor(py::module_&);

PYBIND11_MODULE(core, m) {
  m.doc() = "fsml is a full stack tiny implementation of modern machine learning";

  init_tensor(m);
}
