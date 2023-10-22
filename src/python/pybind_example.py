import fineng_irfx as fe

print("Testing pybind11...\n")
# a and b must be int, they are strongly typed!
a = int(12)
b = int(34)

print(f"Calling c++ 'add'      function: {a} + {b} =", fe.adding(a, b))
print(f"Calling c++ 'subtract' function: {a} - {b} =", fe.subtracting(a, b))

c = 12.2
d = 3.1
print(f"Calling c++ 'times' function: {c} * {d} =", fe.times(c, d), "\n")

U = 0.02
D = - 0.02
R = 0.01
q = fe.L1_riskNeutralProb(U, D, R)
print(f"Risk neutral up prob: q(U,D,R) = q({U},{D},{R}) = {q}", "\n")

print("Success!! :D")

