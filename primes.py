#!/usr/bin/env python
# primes.py - Primes program by Sergey 2015

"""

Helpful functions related to prime numbers and factorization

new(maxn)    - Create an initial structure with precalculated primes up to n
pf(n)        - Prime factor, returns 0 if prime. Sieve of Eratosthenes
is_prime(n)  - Use PF to check for primality
nth_prime(n) - Returns Nth prime number
factorize(n) - Factorize integer, returns map of factors and exponents

Default maxN is 10^5

Time complexity:    O(1), O(N) initialization
Extra space:        O(N)

"""

import unittest
import sys

###############################################################################
# Primes Class (Main Program)
###############################################################################


class Primes:
    """ Primes representation """

    def __init__(self, maxn=10**5):
        """ Default constructor """
        self.pfs = [0] * (maxn + 1)
        self.primes = []
        for i in range(2, maxn + 1):
            if self.pfs[i] == 0:
                self.pfs[i] = i
                self.primes.append(i)
                s = i * i
                if s <= maxn:
                    for j in range(s, maxn + 1, i):
                        self.pfs[j] = i

    def pf(self, n):
        return self.pfs[n]

    def is_prime(self, n):
        return n > 1 and self.pf(n) == n

    def nth_prime(self, n):
        return self.primes[n]

    def factorize(self, n):
        r = dict()
        while n > 1:
            ld = self.pf(n)
            if ld not in r.keys():
                r[ld] = 0
            r[ld] += 1
            n //= ld
        return r

###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    def test_Primes_(self):
        """ Primes class testing """
        d = Primes(20)
        self.assertEqual(d.pf(0), 0)
        self.assertEqual(d.pf(1), 0)
        self.assertEqual(d.pf(2), 2)
        self.assertEqual(d.pf(6), 2)
        self.assertEqual(d.pf(13), 13)
        self.assertEqual(d.pf(8), 2)
        self.assertEqual(d.pf(14), 2)

        # Is prime
        d = Primes(30)
        self.assertEqual(d.is_prime(1), False)
        self.assertEqual(d.is_prime(6), False)
        self.assertEqual(d.is_prime(13), True)
        self.assertEqual(d.is_prime(14), False)

        # Nth prime
        d = Primes()
        self.assertEqual(d.nth_prime(0), 2)
        self.assertEqual(d.nth_prime(5), 13)
        self.assertEqual(d.nth_prime(5), 13)

        # Factorize
        d = Primes(24)
        self.assertEqual(d.factorize(24), {2: 3, 3: 1})

if __name__ == "__main__":
    # Unit tests: -ut
    unittest.main(argv=[" "])
