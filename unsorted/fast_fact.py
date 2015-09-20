#!/usr/bin/env python
# fast_fact.py - fast factorial calculation by Sergey 2015

"""
Fast factorial

"""

# Standard modules
import unittest
import sys

# Additional modules


###############################################################################
# Fast_fact Class
###############################################################################


class Fast_fact:
    """ Fast_fact representation """

    def __init__(self):
        """ Default constructor """

    def next(self, n, anm1, an):
        return (n+1, an, anm1+an if n > 0 else 1)

    def twon(self, n, anm1, an):
        a2n = an * (an + 2 * anm1)
        a2nm1 = an*an + anm1*anm1
        return (n*2, a2nm1, a2n)

    def fastfib(self, n):
        if n == 0:
            return 0
        res = (1, 0, 1)
        ln = list(map(int, bin(n)[2:]))[1:]
        for b in ln:
            res = self.twon(*res)
            if b:
                res = self.next(*res)
        return res[-1]

    def slowfib(self, n):
        if n == 0:
            return 0
        anm1 = 0
        an = 1
        for i in range(1, n):
            an, anm1 = an + anm1, an
        return an

    def run(self, test=False):
        """ Main execution function """

        if test:
            return

###############################################################################
# Executable code
###############################################################################


def main():

    # Sandbox
    sb = Fast_fact(" ".join(sys.argv[1:]))
    sb.run()

###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    def test_Fast_fact_class__basic_functionality(self):
        """ Fast_fact class basic testing """
        d = Fast_fact()

        cur = (0, 0, 0)
        self.assertEqual(d.next(*cur), (1, 0, 1))
        cur = (1, 0, 1)
        self.assertEqual(d.next(*cur), (2, 1, 1))
        cur = (2, 1, 1)
        self.assertEqual(d.next(*cur), (3, 1, 2))
        self.assertEqual(d.twon(*cur), (4, 2, 3))
        self.assertEqual(
            [d.fastfib(i) for i in range(10)],
            [0, 1, 1, 2, 3, 5, 8, 13, 21, 34])
        self.assertEqual(d.slowfib(100), d.fastfib(100))

        import timeit

        start = timeit.default_timer()
        a = d.fastfib(100000)

        fast = timeit.default_timer()
        b = d.slowfib(100000)
        self.assertEqual(a, b)

        stop = timeit.default_timer()
        print(
            "\nTime Test: " +
            "{0:.3f}s (fast {1:.3f}s slow {2:.3f}s)".
            format(stop-start, fast-start, stop-fast))

    def test_Fast_fact_class__run(self):
        """ Main execution function """
        d = Fast_fact()
        d.run(test=True)

if __name__ == "__main__":
    if sys.argv[-1] == "-ut":
        unittest.main(argv=[" "])
    main()
