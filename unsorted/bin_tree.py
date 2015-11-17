#!/usr/bin/env python
# bin_tree.py - Bin_tree program by Sergey 2015

import unittest
import sys

###############################################################################
# Bin_tree Class
###############################################################################


class Node:

    def __init__(self, v=0):
        self.l = None
        self.r = None
        self.v = v

    def is_leaf(self):
        return (self.l is None) and (self.r is None)


class Bin_tree:
    """ Bin_tree representation """

    def __init__(self, args=None):
        """ Default constructor """
        self.R = None

        if args is not None:
            it = iter(args)
            self.R = Node(next(it))
            self.make_tree(self.R, it)

    def make_tree(self, n, it):
        v = next(it)
        if v != -1:
            n.l = Node(v)
            self.make_tree(n.l, it)
        v = next(it)
        if v != -1:
            n.r = Node(v)
            self.make_tree(n.r, it)

    def leafs(self, n=None):
        if n is None:
            n = self.R
        if n.is_leaf():
            return [n]
        else:
            result = []
            if n.l:
                result += self.leafs(n.l)
            if n.r:
                result += self.leafs(n.r)
            return result

    def make_leaf_ll(self):
        lf = self.leafs()
        for i in range(len(lf)-1):
            lf[i].r = lf[i+1]
        return lf[0]


###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    def test_Bin_tree_(self):
        """ Bin_tree class testing """
        d = Bin_tree([1, 2, -1, 3, -1, 5, -1, -1, 6, 7, -1, -1, 8, -1, -1])
        self.assertEqual(d.R.v, 1)
        self.assertEqual(d.R.l.v, 2)
        self.assertEqual(d.R.r.v, 6)
        self.assertEqual(d.R.r.r.r, None)
        self.assertEqual(d.R.l.r.r.v, 5)

        leaf_ll = d.make_leaf_ll()
        self.assertEqual(leaf_ll.v, 5)
        self.assertEqual(leaf_ll.r.v, 7)
        self.assertEqual(leaf_ll.r.r.v, 8)

if __name__ == "__main__":
    unittest.main(argv=[" "])
