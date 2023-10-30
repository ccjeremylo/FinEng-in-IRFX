import fineng_irfx as fe

print("Testing pybind11...\n")
# a and b must be int, they are strongly typed!
a = int(12)
b = int(34)

print(f"Calling c++ function: {a} + {b} =", fe.adding(a, b))
print(f"Calling c++ function: {a} - {b} =", fe.subtracting(a, b))

c = 12.2
d = 3.1
print(f"Calling c++ function: {c} * {d} =", fe.times(c, d), "\n")

U = 0.02
D = -0.02
R = 0.01
q = fe.L1_riskNeutralProb(U, D, R)
print(f"Risk neutral (function): q(U, D, R) = q({U}, {D}, {R}) = {q}", "\n")

L2_BinModel = fe.L2_BinModel(100.0, U, D, R)
q2 = L2_BinModel.RiskNeutralProb()
print(f"Risk neutral (object): q2(U, D, R) = q2({U}, {D}, {R}) = {q2}", "\n")


print("Success!! :D")
