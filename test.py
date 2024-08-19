from fsml.core import Tensor
t1 = Tensor([[1, 2], [3, 4]])
t2 = Tensor([1, 2])
t3 = t1 + t2
print(t3)