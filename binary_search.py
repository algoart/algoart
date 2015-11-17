#!/usr/bin/env python3
# binary_search.py - Binary_search program by Sergey 2015
# AlgoArt - The Art of Algorithms (github.com/algoart/algoart)

"""

Binary search algorithm implementation.

Binary search or half-interval search algorithm finds the position of a target
value within a sorted array

The binary search algorithm can be classified as a dichotomic
divide-and-conquer search algorithm and executes in logarithmic time.

Time complexity:    O(log n)
Extra space:        O(1)

"""

import unittest
import sys

###############################################################################
# Binary_search (Main Program)
###############################################################################


# Find lower bound - leftmost position for new element to be inserted
def lbound(v, n):
    b = 0
    e = len(v)
    while b != e:
        mid = (b + e) // 2
        if v[mid] < n:
            b = mid + 1
        else:
            e = mid
    return b


# Find upper bound - rightmost position for new element to be inserted
def rbound(v, n):
    b = 0
    e = len(v)
    while b != e:
        mid = (b + e) // 2
        if v[mid] <= n:
            b = mid
        else:
            e = mid - 1
    return b


def search(v, n):
    lb = lbound(v, n)
    return -1 if lb == len(v) or v[lb] != n else lb

###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    def test_Binary_search_(self):
        """ Binary_search class testing """

        v = [1, 2, 5, 5, 10, 90]
        self.assertEqual(lbound(v, 0), 0)
        self.assertEqual(lbound(v, 100), 6)

        # Low and upper bounds
        self.assertEqual(lbound(v, 5), 2)
        self.assertEqual(rbound(v, 5), 3)

        # Search
        self.assertEqual(search(v, 11), -1)
        self.assertEqual(search(v, 10), 4)

if __name__ == "__main__":
    # Unit tests: -ut
    unittest.main(argv=[" "])
