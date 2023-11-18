import random

import numpy as np


class RandomGen:
    def __init__(self, initial_seed: int = 1):
        self._seed = initial_seed

    def get_std_normal(self, dim=1):
        self._seed += dim
        np.random.seed(self._seed - dim)
        return np.random.normal(0, 1, dim)

    @property
    def seed(self) -> float:
        """
        Getter method for seed, useful for replicating random results when needed
        """
        return self._seed
