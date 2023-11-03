import math

import fineng_irfx as fe
import numpy as np


class price_asian:
    def __init__(self, S0, sigma, r, T, K, is_call, is_arith, m, RNG):
        self.S0 = S0
        self.sigma = sigma
        self.r = r
        self.T = T
        self.K = K
        self.is_arith = is_arith
        self.m = m
        self.is_call = is_call
        self.RNG = RNG
        if is_arith:
            self.Option = fe.L4_ArithAsian(T, m, K, is_call)
        else:
            self.Option = fe.L4_GeomAsian(T, m, K, is_call)
        self.BSModel = fe.L4_BSModel(S0, r, sigma, RNG)

    def _get_result(self, price, get_error):
        if get_error:
            return price, self.Option.GetPricingError
        return price

    def _pricing(self, path_count):
        if path_count:
            assert type(path_count) == int
            assert path_count > 0
            return self.Option.PriceByMC(self.BSModel, path_count)
        else:
            return self.Option.PriceByFormula(self.BSModel)

    def price_S0(self, S0, path_count=None, get_error=False):
        self.BSModel = fe.L4_BSModel(S0, self.r, self.sigma, self.RNG)
        price = self._pricing(path_count)
        return self._get_result(price, get_error)

    def price_accurate(self, S0, r, sigma, K, T, path_count=None, get_error=False):
        self.BSModel = fe.L4_BSModel(S0, r, sigma, self.RNG)
        if self.is_arith:
            self.Option = fe.L4_ArithAsian(T, self.m, K, self.is_call)
            return self.price_CV(path_count=path_count, get_error=get_error)
        else:
            self.Option = fe.L4_GeomAsian(T, self.m, K, self.is_call)
            return self._pricing(path_count=None)

    def price_CV(self, path_count=100, get_error=False):
        GeomAsian = fe.L4_GeomAsian(self.T, self.m, self.K, self.is_call)
        price = self.Option.PriceByCVMC(self.BSModel, path_count, GeomAsian)
        return self._get_result(price, get_error)
