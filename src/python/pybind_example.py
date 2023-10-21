print("Testing pybind11...\n")

import cmake_example

# a and b must be int, they are strongly typed!
a = 1
b = 2

print(f"Calling c++ 'add'      function: {a} + {b} =", cmake_example.add(a, b))
print(f"Calling c++ 'subtract' function: {a} - {b} =", cmake_example.subtract(a, b), "\n")

print("Success!! :D")

