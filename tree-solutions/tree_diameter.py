# Tree Diameter: https://cses.fi/problemset/task/1131
from collections import defaultdict
import sys

sys.setrecursionlimit(1 << 30)


tree = {}
diameter = [0] * 200001
num_nodes = [0] * 200001


def count_down_paths(tree, src, parent):
    leaf = True
    max_nodes = 0
    for child in tree[src]:
        if parent != child:
            leaf = False
            count_down_paths(tree, child, src)
            max_nodes = max(max_nodes, num_nodes[child])

    if leaf:
        num_nodes[src] = 0
    else:
        num_nodes[src] = 1 + max_nodes


def solve(tree, src, parent):
    child_nodes = []  # child nodes of current src
    ans = 0

    for child in tree[src]:
        if child != parent:
            child_nodes.append(num_nodes[child])
            solve(tree, child, src)
            ans = max(ans, diameter[child])

    n = len(child_nodes)
    child_nodes.sort()

    if n == 0:
        diameter[src] = 0
    elif n == 1:
        diameter[src] = 1 + child_nodes[0]
    else:
        diameter[src] = 2 + child_nodes[n - 1] + child_nodes[n - 2]

    diameter[src] = max(diameter[src], ans)


def main():
    n = int(input())
    tree = defaultdict(list)
    for _ in range(0, n - 1):
        a, b = [int(x) for x in input().split()]
        tree[a].append(b)
        tree[b].append(a)

    count_down_paths(tree, 1, 0)

    solve(tree, 1, 0)
    print(diameter[1])


if __name__ == '__main__':
    main()
