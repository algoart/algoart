#!/usr/bin/env python3
# disjoint_set.py - Disjoint_set program by Sergey 2015
# AlgoArt - The Art of Algorithms (github.com/algoart/algoart)

"""

Disjoint set is a data structure that keeps track of a set of elements
partitioned into a number of disjoint (nonoverlapping) subsets. It supports
following useful operations:

new(n) - Create an initial structure with n subsets

find(n) - Determine which subset a particular element is in. Find typically
returns an item from this set that serves as its "representative",
by comparing the result of two Find operations, one can determine whether two
elements are in the same subset.

join(a, b) - Join two subsets into a single subset

check(a, b) - Check two elements to belong to the same subset

NOTE: Rank heuristic is not included in this library due to a negative
performance effect.

Time complexity:    O(alpha(N))
Extra space:        O(1)

"""

import unittest
import sys

###############################################################################
# Disjoint_set Class (Main Program)
###############################################################################


class Disjoint_set:
    """ Disjoint_set representation """

    def __init__(self, n):
        """ Default constructor """
        self.root = [i for i in range(n+1)]

    def find(self, a):
        r = self.root[a]
        while r != a:
            rr = self.root[r]
            r, self.root[a], a = rr, rr, r
        return a

    def join(self, a, b):
        self.root[self.find(b)] = self.find(a)

    def check(self, a, b):
        return self.find(a) == self.find(b)

###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    def test_Disjoint_set_(self):
        """ Disjoint_set class testing """

        d = Disjoint_set(4)
        d.join(1, 3)
        self.assertEqual(d.find(3), 1)
        self.assertEqual(d.find(2), 2)
        d.join(3, 2)
        self.assertTrue(d.check(2, 1))

        # Performance test
        import random
        nmax = 100000
        d = Disjoint_set(nmax)
        for i in range(nmax//4):
                r = random.randint(0, nmax-100)
                d.find(r)
                d.join(r+1, r+100)
                d.join(r+2, r+99)
                d.join(r+3, r+98)

if __name__ == "__main__":
    # Unit tests: -ut
    unittest.main(argv=[" "])
