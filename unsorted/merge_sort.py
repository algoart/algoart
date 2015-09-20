#!/usr/bin/env python
# merge_sort.py - Merge sort algo by Sergey 2015

"""
Non recursive implementation of the merge sort

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
import math
import time


###############################################################################
# Merge_Sort Class
###############################################################################


class Merge_Sort:
    """ Merge_Sort representation """

    def __init__(self, arg_str=""):
        """ Default constructor """

        # Argument parsing
        self.arg_str = arg_str
        parser = argparse.ArgumentParser(
            description="Merge sort")
        parser.add_argument(
            "array", nargs="*", default="", help="Array elements")
        self.args = parser.parse_args(self.arg_str.split())

        self.set_list([int(x) for x in self.args.array])

    def set_list(self, input_list):
        """ Assign a new list to sort """
        self.list = input_list
        self.list_work = list(self.list)
        self.len = len(self.list)

    def set_random(self, size):
        """ Assign a random list """
        rand_list = []
        for i in range(size):
            rand_list.append(random.randrange(1000))
        self.set_list(rand_list)

    def merge_sort(self, i, n):
        bl_len = 2**n
        starta = bl_len * 2 * i
        startb = bl_len * (2 * i + 1)
        ptra = 0
        ptrb = 0
        enda = (starta + ptra >= self.len)
        endb = (startb + ptrb >= self.len)
        ptr = starta - 1
        while not (enda and endb):
            ptr += 1
            if enda:
                self.list_work[ptr] = self.list[startb + ptrb]
                ptrb += 1
                endb = (ptrb == bl_len) or (startb + ptrb >= self.len)
                continue
            if endb:
                self.list_work[ptr] = self.list[starta + ptra]
                ptra += 1
                enda = (ptra == bl_len) or (starta + ptra >= self.len)
                continue
            a = self.list[starta + ptra]
            b = self.list[startb + ptrb]
            if a < b:
                self.list_work[ptr] = a
                ptra += 1
                enda = (ptra == bl_len) or (starta + ptra >= self.len)
            else:
                self.list_work[ptr] = b
                ptrb += 1
                endb = (ptrb == bl_len) or (startb + ptrb >= self.len)

    def run(self, test=False):
        """ Main execution function """

        if self.len <= 0:
            raise Exception("Empty list is provided!")

        iter_num = math.ceil(math.log(self.len, 2))
        for n in range(iter_num):
            block_num = math.ceil(self.len/(2**(n+1)))
            for i in range(block_num):
                self.merge_sort(i, n)

            # Swap list pointers for each iteration
            tmp = self.list
            self.list = self.list_work
            self.list_work = tmp

        if test:
            return

        print(self.list)

###############################################################################
# Executable code
###############################################################################


def main():

    # Sandbox
    sb = Merge_Sort(" ".join(sys.argv[1:]))
    sb.run()

    for i in range(3):
        d.set_random(5000)
        start_time = time.time()
        d.run(test=True)
        print("Merge Sort: Seconds: ", time.time() - start_time)

    for i in range(3):
        d.set_random(5000)
        start_time = time.time()
        d.list.sort()
        print("Python Sort: Seconds: ", time.time() - start_time)


###############################################################################
# Unit Tests
###############################################################################


class unitTests(unittest.TestCase):

    tmp_area = "/tmp/ut" + getpass.getuser()
    test_area = tmp_area + "/t" + str(random.randrange(10000))
    tmp_file = test_area + "/f" + str(random.randrange(10000))

    test_list = [3, 1, 2, 0, 4, 1]
    test_list_sorted = list(test_list)
    test_list_sorted.sort()

    def setUp(self):
        os.makedirs(self.test_area, exist_ok=True)

    def test_Merge_Sort_class__basic_functionality(self):
        """ Merge_Sort class basic testing """
        d = Merge_Sort("2 4 1 0")
        self.assertEqual(d.args.array, ["2", "4", "1", "0"])
        self.assertEqual(d.list, [2, 4, 1, 0])

        # Assinging a new list
        d.set_list([3, 1])
        self.assertEqual(d.list, [3, 1])

        # Assigning a random list
        d.set_random(10)
        self.assertEqual(len(d.list), 10)

        # Merge sort
        d.set_list(self.test_list)
        d.merge_sort(1, 0)
        self.assertEqual(d.list_work, [3, 1, 0, 2, 4, 1])

    def test_Merge_Sort_class__run(self):
        """ Main execution function """
        d = Merge_Sort()
        d.set_list(self.test_list)
        d.run(test=True)
        self.assertEqual(d.list, self.test_list_sorted)

        # Check lists with random length
        for i in range(20):
            d.set_random(random.randrange(1, 50))
            sorted = list(d.list)
            sorted.sort()
            d.run(test=True)
            self.assertEqual(d.list, sorted)

    def test_xcleanup(self):
        shutil.rmtree(self.tmp_area)

if __name__ == "__main__":
    if sys.argv[-1] == "-ut":
        unittest.main(argv=[" "])
    main()
