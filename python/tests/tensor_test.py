from fsml.Debug.core import Tensor
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

    def test_add(self):
        t1 = Tensor(np.array([1.0, 2.0]))
        t2 = Tensor(np.array([1.0, 2.0]))

        t3 = t1 + t2

        self.assertEqual(t3.size(), 2)
        self.assertEqual(t3.data(), [2.0, 4.0])

    def test_backward(self):
        t1 = Tensor(np.array([1.0, 2.0]))
        t2 = Tensor(np.array([1.0, 2.0]))

        t3 = t1 + t2
        t3.backward()

        self.assertEqual(t3.grad().data(), [1.0, 1.0])
        self.assertEqual(t2.grad().data(), [1.0, 1.0])
        self.assertEqual(t1.grad().data(), [1.0, 1.0])