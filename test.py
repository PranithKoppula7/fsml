from build.python.Debug.core import Tensor
import numpy as np

t = Tensor(5)

t2 = Tensor(5, 3.0)

t3 = Tensor(np.array([1, 2, 3, 4, 5]))

print(t3)

# t4 = Tensor(np.array([[1, 2, 3], [4, 5, 6]]))

print("Working")