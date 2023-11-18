import abc
from typing import final

import numpy as np
import scipy.integrate as integrate


class ShortRateModel(abc.ABC):
    def __init__(self, RNG):
        self._RNG = RNG

    @abc.abstractmethod
    def short_rate(self, T, dim):
        pass

    @abc.abstractmethod
    def df(self, t, T, dim):
        """B(t,T) = E_t[exp( -int_t^T r(u) du )]"""
        pass

    @abc.abstractmethod
    def log_money_market(self, t, dim):
        """ln M(t) = int_0^t r(u) du"""
        pass

    def bond_yield(self, t, T, dim):
        """R(t,T) = -ln B(t,T) / (T-t)"""
        return -np.log(self.df(t, T, dim)) / (T - t)


class Merton(ShortRateModel):
    def __init__(self, r0, drift, vol, RNG):
        self._r0 = r0
        self._theta = drift
        self._vol = vol
        super().__init__(RNG)

    def short_rate(self, t, dim):
        diff = self._vol * np.sqrt(t) * self._RNG.get_std_normal(dim)
        return self._r0 + self._theta * t + diff

    def _log_mm_moments(self, t, T, dim):
        """1st and 2nd moments of: int_t^T r(u) du"""
        Tau = T - t
        mean = -self.short_rate(t, dim) * Tau - 0.5 * self._theta * Tau**2
        variance = (1 / 3.0) * self._vol**2 * Tau**3
        return mean, variance

    def df(self, t, T, dim):
        """bond price"""
        mean, variance = self._log_mm_moments(t, T, dim)
        return np.exp(mean + 0.5 * variance)

    def log_money_market(self, t, dim):
        """log_money_market"""
        mean, variance = self._log_mm_moments(0, t, dim)
        return mean + 0.5 * variance

    def short_rate_moments(self, t):
        mean = self._r0 + self._theta * t
        variance = self._vol**2 * t
        return mean, variance


class Vasicek(ShortRateModel):
    def __init__(self, r0, speed, long_term_mean, vol, RNG):
        self._r0 = r0
        self._k = speed
        self._theta = long_term_mean
        self._vol = vol
        super().__init__(RNG)

    def _f(self, s, u):
        assert u >= s >= 0
        return np.exp(-self._k * (u - s))

    def _int_f(self, s, u):
        """referred to as the G function in notes"""
        assert u >= s >= 0
        return (1.0 - np.exp(-self._k * (u - s))) / self._k

    def _int_f2(self, s, u):
        assert u >= s >= 0
        speed = 2 * self._k
        return (1.0 - np.exp(-speed * (u - s))) / speed

    def short_rate(self, t, dim):
        """
        let f(s,u) = exp[ -k*(u-s) ]
        r(t) = r(0) + f(0,t)*r(0) + theta * int_0^t f(t,u) du + sigma * int_0^t f(t,u) dW_u
        """
        term0 = 0
        term1 = self._f(0, t) * self._r0
        term2 = self._theta * self._int_f(0, t)
        diff = self._vol * np.sqrt(self._int_f2(0, t)) * self._RNG.get_std_normal(dim)
        return term0 + term1 + term2 + diff

    def _log_df(self, t, T, dim):
        int_G = integrate.quad(lambda u: self._int_f(u, T), t, T)[0]
        int_G2 = integrate.quad(lambda u: self._int_f(u, T) ** 2, t, T)[0]
        term0 = self.short_rate(t, dim) * self._int_f(t, T)
        return -term0 - self._theta * int_G + 0.5 * self._vol**2 * int_G2

    def df(self, t, T, dim):
        exponent = self._log_df(t, T, dim)
        return np.exp(exponent)

    def log_money_market(self, t, dim):
        """ln M(t) = int_0^t r(u) du"""
        pass

    def short_rate_moments(self, t):
        mean = self._r0 * self._f(0, t) + self._theta * self._int_f(0, t)
        variance = self._vol**2 * self._int_f2(0, t)
        return mean, variance
