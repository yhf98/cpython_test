#include <Python.h>
#include <numpy/arrayobject.h>
#include <iostream>
#include <stdio.h>

// 矩阵乘法的 C++ 实现
static PyObject* matrix_multiply(PyObject* self, PyObject* args) {
    PyObject *matrix1_obj, *matrix2_obj;
    PyArrayObject *matrix1, *matrix2;

    printf("Test123!!!");

    if (!PyArg_ParseTuple(args, "OO", &matrix1_obj, &matrix2_obj))
        return NULL;

    matrix1 = (PyArrayObject*)PyArray_FROMANY(matrix1_obj, NPY_DOUBLE, 2, 2, NPY_ARRAY_IN_ARRAY);
    matrix2 = (PyArrayObject*)PyArray_FROMANY(matrix2_obj, NPY_DOUBLE, 2, 2, NPY_ARRAY_IN_ARRAY);

    if (matrix1 == NULL || matrix2 == NULL) {
        Py_XDECREF(matrix1);
        Py_XDECREF(matrix2);
        return NULL;
    }

    npy_intp rows1 = PyArray_DIM(matrix1, 0);
    npy_intp cols1 = PyArray_DIM(matrix1, 1);
    npy_intp rows2 = PyArray_DIM(matrix2, 0);
    npy_intp cols2 = PyArray_DIM(matrix2, 1);

    if (cols1 != rows2) {
        PyErr_SetString(PyExc_ValueError, "Incompatible matrix dimensions");
        Py_DECREF(matrix1);
        Py_DECREF(matrix2);
        return NULL;
    }

    // 创建结果矩阵
    npy_intp dims[2] = {rows1, cols2};
    PyObject *result_obj = PyArray_SimpleNew(2, dims, NPY_DOUBLE);
    PyArrayObject *result = (PyArrayObject*)result_obj;

    double *data1 = (double *)PyArray_DATA(matrix1);
    double *data2 = (double *)PyArray_DATA(matrix2);
    double *data_res = (double *)PyArray_DATA(result);

    // 矩阵乘法
    for (npy_intp i = 0; i < rows1; i++) {
        for (npy_intp j = 0; j < cols2; j++) {
            double sum = 0;
            for (npy_intp k = 0; k < cols1; k++) {
                sum += data1[i * cols1 + k] * data2[k * cols2 + j];
            }
            data_res[i * cols2 + j] = sum;
        }
    }

    Py_DECREF(matrix1);
    Py_DECREF(matrix2);
    return result_obj;
}

// 方法表
static PyMethodDef MatrixMethods[] = {
    {"matrix_multiply", matrix_multiply, METH_VARARGS, "Multiplies two matrices"},
    {NULL, NULL, 0, NULL}
};

// 模块定义
static struct PyModuleDef matrixmodule = {
    PyModuleDef_HEAD_INIT,
    "matrix_mult",
    NULL,
    -1,
    MatrixMethods
};

// 初始化模块
PyMODINIT_FUNC PyInit_matrix_mult(void) {
    import_array();  // For NumPy
    return PyModule_Create(&matrixmodule);
}
