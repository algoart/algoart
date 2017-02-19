#!/usr/bin/env python3
# My experiments with DFS/BFS/post/pre order traverse without using recursion

import unittest
import collections
import sys


def walk(update, start):
    stack = [[start]]
    level = 0
    while stack[level]:
        item = stack[level][-1]
        update(stack, level, item)
        stack[level].pop()
        yield item


# def dfs_update(stack, item

# def dfs(next, start):
#    return func1.walk(lambda st, it: st.extend(reversed(next(it))), start)


class func1:

    def walk(update, start):
        stack = collections.deque([start])
        while stack:
            item = stack[-1]
            stack.pop()
            update(stack, item)
            yield item

    def dfs(next, start):
        return func1.walk(lambda st, it: st.extend(reversed(next(it))), start)

    def bfs(next, start):
        return func1.walk(lambda st, it: st.extendleft(next(it)), start)

    def walk_post(update, start):
        stack = collections.deque([start])
        visited = set()
        while stack:
            item = stack[-1]
            if item in visited:
                stack.pop()
                yield item
            else:
                visited.add(item)
                update(stack, item)

    def dfs_post(next, start):
        return func1.walk_post(
            lambda st, it: st.extend(reversed(next(it))), start)


class unitTests(unittest.TestCase):

    def test_dfs_map(self):

        def children(n):
            if n == 0:
                return [1, 2]
            if n == 1:
                return [3]
            else:
                return []
            nodes = 3

        self.assertEqual(list(walk(lambda a, b, c: None, 0)), [0])
        # self.assertEqual(list(dfs(children, 0)), [0, 1, 3, 2])

        self.assertEqual(list(func1.dfs(children, 0)), [0, 1, 3, 2])
        self.assertEqual(list(func1.bfs(children, 0)), [0, 1, 2, 3])
        self.assertEqual(list(func1.dfs_post(children, 0)), [3, 1, 2, 0])

if sys.argv[-1] == "-ut":
    unittest.main(argv=[" "])
