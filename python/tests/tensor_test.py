from fsml.core import Tensor
import numpy as np
import unittest

class TensorTest(unittest.TestCase):

    def test_init_int(self):
        t = Tensor(5)

        self.assertEqual(t.size(), 1)
        self.assertEqual(t.data(), [5.0])

    def test_init_float(self):
        t = Tensor(3.0)

        self.assertEqual(t.size(), 1)
        self.assertEqual(t.data(), [3.0])
    
    def test_init_np_array(self):
        t = Tensor(np.array([1.0, 2.0]).astype(float))

        self.assertEqual(t.size(), 2)
        self.assertEqual(t.data(), [1.0, 2.0])

    def test_shape_scalar(self):
        t = Tensor(1.0);

        self.assertEqual(t.shape(), [])

    def test_shape_array(self):
        t = Tensor([1, 2]);

        self.assertEqual(t.shape(), [2])

    def test_shape_2d(self):
        t = Tensor([[1, 2], [3, 4]])

        self.assertEqual(t.shape(), [2, 2])

    def test_shape_2d_unequal(self):
        t = Tensor([[1, 2], [1, 2], [1, 2]])

        self.assertEqual(t.shape(), [3, 2])

    def test_shape_3d(self):
        t = Tensor([[[1, 2], [3, 4]]])

        self.assertEqual(t.shape(), [1, 2, 2])

    def test_add_tensor(self):
        t1 = Tensor(np.array([1.0, 2.0]))
        t2 = Tensor(np.array([1.0, 2.0]))

        t3 = t1 + t2

        self.assertEqual(t3.size(), 2)
        self.assertEqual(t3.data(), [2.0, 4.0])

    def test_add_int(self):
        t1 = Tensor(np.array([1.0, 2.0]));

        t2 = t1 + 1;

        self.assertEqual(t2.size(), 2);
        self.assertEqual(t2.data(), [2.0, 3.0]);

    def test_add_float(self):
        t1 = Tensor(np.array([1.0, 2.0]));

        t2 = t1 + 1.0;

        self.assertEqual(t2.size(), 2);
        self.assertEqual(t2.data(), [2.0, 3.0]);

    def test_backward(self):
        t1 = Tensor(np.array([1.0, 2.0]))
        t2 = Tensor(np.array([1.0, 2.0]))

        t3 = t1 + t2
        t3.backward()

        self.assertEqual(t3.grad().data(), [1.0, 1.0])
        self.assertEqual(t2.grad().data(), [1.0, 1.0])
        self.assertEqual(t1.grad().data(), [1.0, 1.0])
