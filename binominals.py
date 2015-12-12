#!/usr/bin/env python3
# binominals.py - Binominals program by Sergey 2015
# AlgoArt - The Art of Algorithms (github.com/algoart/algoart)

"""

Calculating binominal coefficients, factorials, inverted factorials, fast
exponents, modulo operations etc.

Modulos(mod) - modulo selection
mod(a)      - Modulo operation
add(a,b)    - Modulo addition
mul(a,b)    - Modulo multiplication
pow(e,n)    - Modulo power (using binary exponent)
inv(a)      - Modulo inverse function, i.e. mul(a, inv(a)) == 1

Binominals(mod, maxn) - modulo and max N selection
fact(n)     - Factorial
ifact(n)    - Factorial inverse function
P(n,k)      - Number of permutations
C(n,k)      - Binominal Coefficients

Default modulo is 10^9+7 and default max N is 10^5.

NOTE: Modulo needs to be a prime number. Operands for all
modulo functions need to be less than modulo.

Time complexity:    O(1), O(N) - initialization
Extra space:        O(N)

"""

import unittest
import sys

###############################################################################
# Modulos Class
###############################################################################


class Modulos:

    def __init__(self, mod=(10**9)+7):
        self.m = mod

    def mod(self, a):
        return a % self.m

    def add(self, a, b):
        return (a + b) % self.m

    def mul(self, a, b):
        return (a * b) % self.m

    def pow(self, e, n):
        r = 1
        while n > 0:
            if n & 1:
                r = self.mul(r, e)
            e = self.mul(e, e)
            n >>= 1
        return r

    def inv(self, a):
        return self.pow(a, self.m-2)


###############################################################################
# Binominals Class (Main Program)
###############################################################################


class Binominals(Modulos):
    """ Binominals representation """

    def __init__(self, mod=(10**9)+7, maxn=10**5):
        self.m = mod

        # Factorials
        self.facts = [0] * (maxn+1)
        for i in range(maxn+1):
            self.facts[i] = self.mul(self.facts[i-1], i) if i > 0 else 1

        # Inverse factorial
        self.ifacts = [0] * (maxn+1)
        for i in range(maxn, -1, -1):
            self.ifacts[i] = (self.mul(self.ifacts[i+1], i+1) if i < maxn
                              else self.inv(self.fact(maxn)))

    def fact(self, n):
        return self.facts[n]

    def ifact(self, n):
        return self.ifacts[n]

    def P(self, n, k):
        return self.mul(self.fact(n), self.ifact(n-k))

    def C(self, n, k):
        return self.mul(self.P(n, k), self.ifact(k))


###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    def test_Modulos(self):
        """ Modulos class testing """
        d = Modulos()
        self.assertEqual(d.add(4, 5), 9)
        self.assertEqual(d.mul(4, 5), 20)
        self.assertEqual(d.pow(4, 5), 1024)

    def test_Binominals(self):
        """ Binominals class testing """
        d = Binominals(maxn=0)

        self.assertEqual(d.add(4, 5), 9)
        self.assertEqual(d.mul(4, 5), 20)
        self.assertEqual(d.pow(4, 5), 1024)

        # Small modulo operations
        d = Binominals(mod=23, maxn=0)
        self.assertEqual(d.add(4, 5), 9)
        self.assertEqual(d.mul(4, 5), 20)
        self.assertEqual(d.pow(4, 5), 12)
        for i in range(1, 10):
            self.assertEqual(d.mul(i, d.inv(i)), 1)

        # Precomputed factorials
        d = Binominals(mod=(1 << 30) - 35, maxn=5)
        self.assertEqual(d.fact(0), 1)
        self.assertEqual(d.fact(1), 1)
        self.assertEqual(d.fact(4), 24)

        # Base larger than int
        d = Binominals(mod=(1 << 62) - 57)

        # Precomputed inverted factorials
        for i in range(1000, 1010):
            self.assertEqual(d.mul(d.fact(i), d.ifact(i)), 1)

        # Permutations Pn,k
        self.assertEqual(d.P(7, 5), 2520)

        # Binominal Coefficient Cn,k
        self.assertEqual(d.C(7, 4), 35)

if __name__ == "__main__":
    # Unit tests: -ut
    unittest.main(argv=[" "])
