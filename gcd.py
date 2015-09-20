#!/usr/bin/env python
# gcd.py - Gcd program by Sergey 2015

"""

In mathematics, the greatest common divisor (gcd) of two or more integers,
when at least one of them is not zero, is the largest positive integer that
divides the numbers without a remainder. For example, the GCD of 8 and 12 is 4.

In arithmetic and number theory, the least common multiple of two integers
a and b, usually denoted by LCM(a, b), is the smallest positive integer that
is divisible by both a and b.

LCM(a,b) = |a*b| / GCD(a, b)

Time complexity:    O(log a + log b)
Extra space:        O(1)

"""

import unittest
import sys

###############################################################################
# Gcd (Main Program)
###############################################################################


# Euclidean GCD algorithm
def gcd(a, b):
    while b != 0:
        (a, b) = (b, a % b)
    return a


# Using GCD to calculate LCM
def lcm(a, b):
    return a * b // gcd(a, b)


###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    def test_Gcd_(self):
        """ Gcd class testing """

        # Euclidean algo
        self.assertEqual(gcd(0, 0), 0)
        self.assertEqual(gcd(100, 0), 100)
        self.assertEqual(gcd(8, 2), 2)
        self.assertEqual(gcd(30, 42), 6)
        self.assertEqual(lcm(10, 15), 30)

        # Performance
        import random
        for i in range(10000):
            gcd(random.randint(0, 1000000), random.randint(0, 1000000))

if __name__ == "__main__":
    # Unit tests: -ut
    unittest.main(argv=[" "])
