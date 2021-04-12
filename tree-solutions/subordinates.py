# https://cses.fi/problemset/task/1674
from collections import deque, defaultdict, Counter, OrderedDict
from math import ceil, sqrt, hypot, factorial, pi, sin, cos, radians
from heapq import heappush, heappop, heapify, nlargest, nsmallest
import os
import sys

sys.setrecursionlimit(1 << 30)
from io import BytesIO, IOBase
import math
import bisect
from math import inf
import random

ins = lambda: [int(x) for x in input()]
inp = lambda: int(input())
inps = lambda: [int(x) for x in input().split()]
import sys

sys.setrecursionlimit(1 << 30)

mod = pow(10, 9) + 7

n = inp()
emp_ids = inps()

tree = {}

for (idx, id) in enumerate(emp_ids):
    if id not in tree:
        tree[id] = []
    tree[id].append(idx + 2)


# print(tree)

def dfs(tree, current):
    count = 0

    for child in tree.get(current, []):
        count += 1 + dfs(tree, child)

    # print(count)
    ans[current - 1] = count
    return count


ans = [0] * (n)
dfs(tree, 1)

print(" ".join(map(str, ans)))
