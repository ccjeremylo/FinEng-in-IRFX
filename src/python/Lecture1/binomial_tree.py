import binomial_tree
import fineng_irfx as fe
import numpy as np


class BinomialTree:
    def __init__(self, S0, sigma, r, K, T, N, style):
        # set market param
        self._S0 = S0
        self._sig = sigma
        self._r = r

        # set option param
        self._T = T
        self._K = K

        # convenient param
        self._a = np.exp(r * T / N)
        self._b = np.exp((2 * r + sigma**2) * T / N)
        self._diff = sigma * np.sqrt(T / N)

        # set tree param/style
        self._availiable_style = [
            "CRR",
            "JR",
            "v-drift",
            "geometric-centred-strike",
            "arithmetic-centred-strike",
        ]
        assert style in self._availiable_style
        self._style = style
        self._N = N
        self._dt = T / N
        self._R = np.exp(r * T / N) - 1.0
        self._set_U_D()
        self._q = self._Q(self._U, self._D, self._R)

    @property
    def style(self):
        return self._style

    @property
    def q(self):
        return self._q

    @property
    def U(self):
        return self._U

    @property
    def D(self):
        return self._D

    @property
    def R(self):
        return self._R

    @property
    def N(self):
        return self._N

    def _check_tree(self, tolerance=3e-3):
        u = self._U + 1.0
        d = self._D + 1.0
        LHS = self._a * (u + d) - d * u
        RHS = self._b
        assert abs(LHS - RHS) - 0.0 < tolerance, f"{LHS} != {RHS}"

    def _Q(self, U, D, R):
        return fe.L1_riskNeutralProb(U, D, R)

    def _quadratic_solver(self, A, B, C, upper=True):
        discriminant = np.sqrt(B**2 - 4 * A * C)
        if upper:
            return (-B + discriminant) / (2 * A)
        return (-B - discriminant) / (2 * A)

    def _CRR(self):
        """
        Cox-Ross-Rubinstein: ud = 1
        There are 2 possible solutions for u
        We pick the upper one:
        u^2 -((1+b)/a)*u +1 = 0
        """
        B = -(1.0 + self._b) / self._a
        u = self._quadratic_solver(1.0, B, 1.0, True)
        self._U = u - 1.0
        self._D = 1.0 / (self._U + 1.0) - 1.0
        assert abs(u * (self._D + 1.0) - 1.0) < 1e-7, f"{1+self._U} * {1+self._D} != 1"

    def _JR(self):
        """
        Jarrow and Rudd: q = 0.5
        There are 2 possible solutions for u
        We pick the upper one:
        """
        A = 10.0
        B = -12.0 * self._a
        C = 4.0 * self._a**2 - 2 * self._b
        u = self._quadratic_solver(A, B, C, True)
        self._U = u - 1.0
        self._D = 3 * u - 2 * self._a - 1.0
        q = (self._a - u) / (u - self._D - 1.0)
        assert abs(q - 0.5) < 1e-7, f"{q} != 0.5"

    def _get_u_d_by_v(self, v):
        u = np.exp(v * self._dt + self._diff)
        d = np.exp(v * self._dt - self._diff)
        return u, d

    def _set_U_D_by_v(self, v):
        u, d = self._get_u_d_by_v(v)
        self._U = u - 1.0
        self._D = d - 1.0

    def _set_U_D(self):
        match self._style:
            case "CRR":
                self._CRR()

            case "JR":
                self._JR()

            case "v-drift":
                v = self._r + 0.5 * self._sig
                self._set_U_D_by_v(v)

            case "geometric-centred-strike":
                v = np.log(self._K / self._S0) / (2 * self._N * self._dt)
                self._set_U_D_by_v(v)

            case "arithmetic-centred-strike":
                const = 2 * np.cosh(self._N * self._diff)
                v = np.log(self._K / self._S0 / const) / (self._N * self._dt)
                self._set_U_D_by_v(v)

        self._check_tree()

    def S_T(self, i):
        return fe.L1_S(self._S0, self._U, self._D, self._N, i)

    def prob(self, i):
        return (
            fe.L1_NewtonSymb(self._N, i) * self._q**i * (1 - self._q) ** (self._N - i)
        )
