"""
A Fenwick tree or binary indexed tree is a data structure that can efficiently update elements and calculate prefix sums in a table of numbers.
"""


class FenwickTree:
    def __init__(self, array):
        self.array = array
        for i in range(len(array)):
            self.update(i, array[i])

    def update(self, idx, value):
        while idx < len(self.array):
            self.array[idx] += value
            idx += idx & -idx

    def summation(self, idx):
        res = 0
        while idx >= 0:
            res += self.array[idx]
            idx -= idx & -idx
        return res
