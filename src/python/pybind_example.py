import cmake_example as ce

print("Testing pybind11...\n")
# a and b must be int, they are strongly typed!
a = int(12)
b = int(34)

print(f"Calling c++ 'add'      function: {a} + {b} =", ce.adding(a, b))
print(f"Calling c++ 'subtract' function: {a} - {b} =", ce.subtracting(a, b), "\n")

c = 12.2
d = 3.1
print(f"Calling c++ 'times' function: {c} * {d} =", ce.times(c, d), "\n")

print("Success!! :D")

