#include "broadcasting.h"

broadcasting::broadcasting(std::vector<tensor> tensors) {
    this->tensors = tensors;

    std::vector<std::vector<int>> shapes;
    for (tensor t: tensors) {
      shapes.push_back(t.shape());
    }
    
    // shape
    this->shape = broadcast_shape(shapes);
    // ndim
    this->ndim = this->shape.size();
    // size
    int _size = 1;
    for (int s: shape) {
      _size *= s;
    }
    this->size = _size;
}

std::vector<int> broadcasting::getShape() {
  return this->shape;
}

int broadcasting::getNdim() {
  return this->ndim;
}

int broadcasting::getSize() {
  return this->size;
}

std::vector<tensor> broadcasting::broadcast() {
  std::vector<tensor> ans;
  for (tensor t: this->tensors) {
    ans.push_back(broadcast(t, this->shape));
  }
  return ans;
}

tensor broadcasting::broadcast(tensor& a, std::vector<int> shape) {
  if (a.shape().size() > shape.size()) {
    throw std::runtime_error(
      "broadcasting.broadcast line 33 - cannot broadcast tensor!"
    );
  }
  std::vector<float> data;
  float* a_data = a.data();
  int boundary = a.size();
  for (int i = 0; i < size; i++) {
    data.push_back(a_data[i % boundary]);
  }
  return tensor(data, shape);
}


// tensor broadcasting::broadcast_to(tensor& x, std::vector<int> shape) {
//   if (x.shape() == shape) return x;

//   int diff = shape.size() - x.size();
//   std::vector<size_t> strides(shape.size(), 0);
//   for (int i = x.shape().size() - 1; i >= 0; i--) {
//     strides[i + diff] = x.shape()[i] == 1 ? 0 : x.data_.strides()[i];
//   }

//   return tensor(buffer<float>(shape, x.data_vec, strides));
// }

std::vector<std::vector<int>> broadcasting::pad_left(
    std::vector<std::vector<int>> shapes) {
  int max = 0;
  for (std::vector<int> s: shapes) {
    max = std::max(max, (int)s.size());
  }

  std::vector<std::vector<int>> ans;
  for (std::vector<int> s: shapes) {
    if (s.size() == max) {
      ans.push_back(s);
    } else {
      std::vector<int> s_;
      int numOnes = max - s.size();
      for (int i = 0; i < numOnes; i++) {
        s_.push_back(1);
      }
      for (int i = 0; i < s.size(); i++) {
        s_.push_back(s[i]);
      }
      ans.push_back(s_);
    }
  }

  return ans;
}

std::vector<int> broadcasting::broadcast_shape(
    std::vector<std::vector<int>> shapes) {
  if (shapes.size() == 0) {
    throw std::invalid_argument(
      "broadcasting.broadcast_shape, line: 67 - arg shapes is empty!"
    );
  }

  std::vector<std::vector<int>> padded = pad_left(shapes);

  int size = padded[0].size();
  std::vector<int> ans;
  for (int i = 0; i < size; i++) {
    int currDimMax = 0;
    for (std::vector<int> s: padded) {
      currDimMax = std::max(currDimMax, s[i]);
    }
    ans.push_back(currDimMax);
  }
  return ans;
}
