import fineng_irfx as fe
import numpy as np
import math

class price_barrier:
    def __init__(self, S0, sigma, r, T, K, Bup, Bdown, isCall, isKO, m, RNG):
        self.S0 = S0
        self.sigma = sigma
        self.r = r
        self.T = T
        self.K = K
        self.Bup = Bup
        self.Bdown = Bdown
        self.isKO = isKO
        self.m = m
        self.isCall = isCall
        self.RNG = RNG
        if self.isKO:
            self.DB = fe.L4_DoubleBarrierKO(T, m, K, Bup, Bdown, isCall)
        else:
            self.DB = fe.L4_DoubleBarrierKI(T, m, K, Bup, Bdown, isCall)
        self.BSModel = fe.L4_BSModel(S0, r, sigma, RNG)
        
    def price_S0(self, S0, path_count, get_error=False):
        self.BSModel = fe.L4_BSModel(S0, self.r, self.sigma, self.RNG)
        price = self.DB.PriceByMC(self.BSModel, path_count)
        if get_error:
            return price, self.DB.GetPricingError
        return price

    def price_B(self, Bup, Bdown, path_count, get_error=False):
        if self.isKO:
            self.DB = fe.L4_DoubleBarrierKO(self.T, self.m, self.K, Bup, Bdown, self.isCall)
        else:
            self.DB = fe.L4_DoubleBarrierKI(self.T, self.m, self.K, Bup, Bdown, self.isCall)
        price = self.DB.PriceByMC(self.BSModel, path_count)
        if get_error:
            return price, self.DB.GetPricingError
        return price

    def price_K(self, K, path_count, get_error=False):
        if self.isKO:
            self.DB = fe.L4_DoubleBarrierKO(self.T, self.m, K, self.Bup, self.Bdown, self.isCall)
        else:
            self.DB = fe.L4_DoubleBarrierKI(self.T, self.m, K, self.Bup, self.Bdown, self.isCall)
        price = self.DB.PriceByMC(self.BSModel, path_count)
        if get_error:
            return price, self.DB.GetPricingError
        return price

    def price(self, path_count, get_error=False):
        price = self.DB.PriceByMC(self.BSModel, path_count)
        if get_error:
            return price, self.DB.GetPricingError
        return price

    def price_CV(self, path_count, get_error=False):
        Vanilla = fe.L4_Vanilla(self.T, self.m, self.K, self.isCall)
        price = self.DB.PriceByVanillaCVMC(self.BSModel, path_count, Vanilla)
        if get_error:
            return price, self.DB.GetPricingError
        return price
        










        