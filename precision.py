#!/usr/bin/env python3
# precision.py - Precision program by Sergey 2015
# AlgoArt - The Art of Algorithms (github.com/algoart/algoart)

"""

Arbitrary precision math calculations.

decimal.getcontext().prec = p - setting the precision (Default: 40)

pi() - Calculates Pi with required precision

PI - precalculated value of Pi

inv(x, b, e, f) - calculates inverse function for a growing function f (b < e)

sin(x)/cos(x)/tan() - sine, cosine and tan functions

asin(x)/acos(x)/atan(x) - arcsine, arccosine and arctan functions

Time complexity:    O(p^2)

"""

import unittest
import sys
import decimal

###############################################################################
# Precision (Main Program)
###############################################################################


# Default precision
decimal.getcontext().prec = 30


def pi():
    decimal.getcontext().prec += 2
    three = decimal.Decimal(3)
    lasts, t, s, n, na, d, da = 0, three, 3, 1, 0, 0, 24
    while s != lasts:
        lasts = s
        n, na = n+na, na+8
        d, da = d+da, da+32
        t = (t * n) / d
        s += t
    decimal.getcontext().prec -= 2
    return +s


PI = pi()


def inv(x, b, e, f):
    decimal.getcontext().prec += 2
    while True:
        mid = (b + e) / 2
        if mid == e or mid == b:
            break
        if f(mid) <= x:
            b = mid
        else:
            e = mid
        dlog = decimal.Decimal(e - b).copy_abs().log10()
        if dlog <= -decimal.getcontext().prec:
            break
    decimal.getcontext().prec -= 2
    return +b


def sin(x):
    decimal.getcontext().prec += 2
    x = x.remainder_near(PI * 2)
    i, lasts, s, fact, num, sign = 1, 0, x, 1, x, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    decimal.getcontext().prec -= 2
    return +s


def cos(x):
    return sin(x + PI/2)


def tan(x):
    return sin(x)/cos(x)


def asin(x):
    return inv(x, -PI/2, PI/2, sin)


def acos(x):
    return PI/2 - asin(x)


def atan(x):
    return asin(x / (x*x + 1).sqrt())


###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    def test_Precision_(self):
        """ Precision class testing """

        # Pi
        self.assertEqual(PI, pi())

        # Inv
        self.assertEqual(inv(10, 1, 100, abs), 10)

        # Sin/Cos/Tan
        invsq2 = 1 / decimal.Decimal(2).sqrt()
        self.assertEqual(sin(PI * 100), 0)
        self.assertAlmostEqual(sin(PI/4 + 2*PI), invsq2)
        self.assertAlmostEqual(cos(PI/4), invsq2)
        for i in range(50):
            t = decimal.Decimal(0.1*(i-25))
            self.assertAlmostEqual(cos(t)**2 + sin(t)**2, 1)
        self.assertAlmostEqual(tan(PI/4), 1)

        # Asin/Acos/Atan
        for i in range(5):
            t = decimal.Decimal(0.1*(i-2))
            self.assertAlmostEqual(asin(sin(t)), t)
            self.assertAlmostEqual(atan(tan(t)), t)


if __name__ == "__main__":
    # Unit tests: -ut
    unittest.main(argv=[" "])
