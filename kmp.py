#!/usr/bin/env python3
# kmp.py - KMP program by Sergey 2016
# AlgoArt - The Art of Algorithms (github.com/algoart/algoart)

"""

In computer science, the Knuth-Morris-Pratt string searching algorithm
(or KMP algorithm) searches for occurrences of a "word" W within a main
"text string" S by employing the observation that when a mismatch occurs, the
word itself embodies sufficient information to determine where the next match
could begin, thus bypassing re-examination of previously matched characters.

A string matching algorithm wants to find the starting index m in string S[n]
that matches the search word W[k]

Time complexity:    O(n+k)
Extra space:        O(k)

"""

import unittest
import sys

###############################################################################
# KMP (Main Program)
###############################################################################


# KMP partial match table
def kmp_table(W):
    assert(len(W) > 0)
    cnd = -1
    T = [-1]
    for i in range(len(W)):
        while True:
            if cnd == -1 or W[cnd] == W[i]:
                cnd += 1
                T.append(cnd)
                break
            cnd = T[cnd]
    return T


# KMP search
def kmp_search(W, S):
    cnd = 0
    T = kmp_table(W)
    for i in range(len(S)):
        while True:
            if cnd == -1 or W[cnd] == S[i]:
                cnd += 1
                break
            cnd = T[cnd]
        if cnd == len(W):
            return i - cnd + 1
    return -1


###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    def test_Kmp_(self):
        """ Gcd class testing """

        # KMP table generation
        self.assertEqual(kmp_table("A"), [-1, 0])
        self.assertEqual(kmp_table("AA"), [-1, 0, 1])
        self.assertEqual(kmp_table("AB"), [-1, 0, 0])
        self.assertEqual(kmp_table("ABAB"), [-1, 0, 0, 1, 2])
        self.assertEqual(kmp_table("ABCDABA"), [-1, 0, 0, 0, 0, 1, 2, 1])

        # KMP search
        self.assertEqual(kmp_search("A", ""), -1)
        self.assertEqual(kmp_search("AB", "B"), -1)
        self.assertEqual(kmp_search("A", "BBBB"), -1)
        self.assertEqual(kmp_search("A", "A"), 0)
        self.assertEqual(kmp_search("BA", "BA"), 0)
        self.assertEqual(kmp_search("A", "BA"), 1)
        self.assertEqual(kmp_search("AS", "BDAS"), 2)
        self.assertEqual(kmp_search("ABAC", "ABABABACB"), 4)

if __name__ == "__main__":
    # Unit tests: -ut
    unittest.main(argv=[" "])
