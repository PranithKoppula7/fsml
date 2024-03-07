from build.python.Debug.core import Tensor
import numpy as np

t = Tensor(5)
print(t)

t2 = Tensor(5, 3.0)
print(t2)

t3 = t + t2
print(t3)

t3.backward()
print(t)
print(t2)
print(t3)

t4 = Tensor(np.array([1.0, 2.0]).astype(float))
print(t4)

t5= Tensor(np.array([2.0, 3.0]).astype(float))
print(t5)
print(t4)

t6 = t4 + t5

t6.backward()

print(t6)
print(t5)
print(t4)