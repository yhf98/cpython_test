import numpy as np
import matrix_mult

# 定义两个矩阵
matrix1 = np.array([[1, 2], [3, 4]], dtype=np.double)
matrix2 = np.array([[5, 6], [7, 8]], dtype=np.double)

# 调用 C++ 扩展中的函数
result = matrix_mult.matrix_multiply(matrix1, matrix2)
print(result)
