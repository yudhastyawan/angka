# Angka

[![Documentation Status](https://readthedocs.org/projects/angka/badge/?version=latest)](https://angka.readthedocs.io/en/latest/?badge=latest)
[![PyPI version](https://badge.fury.io/py/angka.svg)](https://badge.fury.io/py/angka)
[![GitHub issues](https://img.shields.io/github/issues/yudhastyawan/angka)](https://github.com/yudhastyawan/angka/issues)
[![GitHub forks](https://img.shields.io/github/forks/yudhastyawan/angka)](https://github.com/yudhastyawan/angka/network)
[![GitHub stars](https://img.shields.io/github/stars/yudhastyawan/angka)](https://github.com/yudhastyawan/angka/stargazers)
[![GitHub license](https://img.shields.io/github/license/yudhastyawan/angka)](https://github.com/yudhastyawan/angka/blob/main/LICENSE)

a repository focusing on data processing package namely angka. 
It focuses on matrix data manipulating and visualization in C.
The project is an initial step for the applied focuses, especially
earth science purposes. We also have a goal to wrap this library to
another language such as Python.

### The important links

- Documentation: http://angka.readthedocs.io

## Python examples

### Example 1:
```python
>>> from angka import *
# create and set the size of vector
>>> vec = AgxVector(10)
# change the value of each element to be a random value
>>> vec.random(-15,15)
>>> print(vec)
10 [14.45432, -9.45448, 5.05157, -6.45054,..., 13.44721]

# force to change all element to be a value.
>>> vec <<= 4.
>>> print(vec) 
10 [4.00000, 4.00000, 4.00000, 4.00000,..., 4.00000]
```

### Example 2:
```python
>>> from angka import * 
>>> vec = AgxVector(8)  
>>> vec.random(-15,15)  
>>> print(vec)          
8 [14.78667, 2.83684, -9.52864, 8.94909,..., -9.82345]

# we can change all element in existing vector and create linspace
>>> vec.linspace(0., 15.)
>>> print(vec)
8 [0.00000, 1.87500, 3.75000, 5.62500,..., 13.12500]

# append a value in the end of vector
>>> vec.append(10.)
>>> print(vec)      
9 [0.00000, 1.87500, 3.75000, 5.62500,..., 10.00000]

# copy vector
>>> vec2 = vec.copy()
>>> vec2.random(-12,4)
>>> print(vec2)
9 [0.78505, -10.04876, -4.48951, -8.66396,..., 2.14642]

# using built-in len() python
>>> len(vec2)
9
>>> vec3 = vec2 << 5.
>>> print(vec3)
9 [5.00000, 5.00000, 5.00000, 5.00000,..., 5.00000]

# vector added by a value
>>> vec4 = vec3 + 5  
>>> print(vec4)     
9 [10.00000, 10.00000, 10.00000, 10.00000,..., 10.00000]

# built-in in
>>> 10. in vec4 
True
>>> 8. in vec4  
False

# iteration using for ... in ...
>>> for x in vec2:
...     print(x)
... 
0.7850581377605526
-10.048768578142644
-4.489516891994995
-8.663960692159794
3.3110141300698874
-5.852351451155125
2.0018921475875118
-8.59706411938841
2.146427808465834

# print all elements in the vector
>>> vec2.printFull()
9 [0.78505, -10.04876, -4.48951, -8.66396, 3.31101, -5.85235, 2.00189, -8.59706, 2.14642]
```

### Example 3:
```python
>>> import numpy as np
>>> npa = np.array([1,2,3]) 

# numpy to vector
>>> vec = AgxVector(npa)
>>> print(vec)
3 [1.00000, 2.00000, 3.00000]

# vector to numpy
>>> vec.toNumpy()
array([1., 2., 3.])
```