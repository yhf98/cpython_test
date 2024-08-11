from setuptools import setup, Extension
import numpy

# 定义 C++ 扩展模块
module = Extension(
    'matrix_mult',
    sources=['matrix_mult.cpp'],
    include_dirs=[numpy.get_include()],
    extra_compile_args=['-O3', '-std=c++11'],
    language='c++'
)

setup(
    name='matrix_mult',
    version='1.0',
    description='Matrix multiplication C++ extension module',
    ext_modules=[module],
)
