#!/usr/bin/env python3
# My experiments with queue recursion

import unittest
import sys


def fib(n):
    if n < 2:
        return n
    return fib(n-2) + fib(n-1)


def step(n, mem, ):
    if n < 2:
        return n
    else:
        return


def fib2(n):
    nl = set([n])
    fm = dict()
    while nl:
        if len(nl) > 100:
            print(nl)
            raise AssertionError("Recursion overflow")

        n = nl.pop()

        if n < 2:
            fm[n] = n
        else:
            if n-1 not in fm:
                nl.add(n)
                nl.add(n-1)
            elif n-2 not in fm:
                nl.add(n)
                nl.add(n-2)
            else:
                fm[n] = fm[n-2] + fm[n-1]
        # print(nl)

    return fm[n]


def fact(n):
    if n == 0:
        return 1
    return n*fact(n-1)


def fact2(n):
    todo_list = [n]
    todo_memo = dict()
    while todo_list:
        if len(todo_list) > 100:
            print(todo_list)
            raise AssertionError("Recursion overflow")

        todo = todo_list.pop()

        if todo == 0:
            todo_memo[todo] = 1
        else:
            if todo-1 in todo_memo:
                todo_memo[todo] = todo * todo_memo.pop(todo-1, None)
            else:
                todo_list.append(todo)
                todo_list.append(todo-1)

    return todo_memo[n]


def antirec(f, l):
    pass


class unitTests(unittest.TestCase):

    def test_fib(self):
        self.assertEqual(fib(6), 8)
        self.assertEqual(fib2(6), 8)

    def test_fact(self):
        self.assertEqual(fact(4), 24)
        self.assertEqual(fact2(4), 24)

if sys.argv[-1] == "-ut":
    unittest.main(argv=[" "])
