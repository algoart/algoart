#!/usr/bin/env python
# linked_list.py - Linked list implementation in Python by Sergey 2015

"""
Linked list implementation in Python

"""

# Standard modules
import unittest
import sys
import os
import argparse
import re
import random
import subprocess
import getpass
import shutil

# Additional modules


###############################################################################
# Linked_list Class
###############################################################################

class Node:
    def __init__(self, value, tail):
        self.value = value
        self.next = tail


class Linked_list:
    """ Linked_list representation """

    def __init__(self):
        """ Default constructor """
        self.list = None

    def insert(self, value):
        self.list = Node(value, self.list)

    def start_iter(self):
        return self.list

    def next_iter(self, iter):
        if iter is not None:
            return iter.next
        else:
            return iter

    def tolist(self):
        result = []
        iter = self.start_iter()
        while True:
            result.append(iter.value)
            iter = self.next_iter(iter)
            if not iter:
                break
        return result

    def run(self, test=False):
        """ Main execution function """

        if test:
            return

###############################################################################
# Executable code
###############################################################################


def main():

    # Sandbox
    sb = Linked_list(" ".join(sys.argv[1:]))
    sb.run()

###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    def test_Linked_list_class__basic_functionality(self):
        """ Linked_list class basic testing """
        d = Linked_list()
        self.assertEqual(d.list, None)
        d.insert(1)
        self.assertEqual(d.list.value, 1)
        d.insert(2)
        self.assertEqual(d.list.next.value, 1)

        iter = d.start_iter()
        self.assertEqual(iter.value, 2)
        iter = d.next_iter(iter)
        self.assertEqual(iter.value, 1)

        self.assertEqual(d.tolist(), [2, 1])

if __name__ == "__main__":
    if sys.argv[-1] == "-ut":
        unittest.main(argv=[" "])
    main()
