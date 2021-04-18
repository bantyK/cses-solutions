# https://cses.fi/problemset/task/1132
from collections import defaultdict

depths = [0] * 200001
ans = [0] * 200001

MIN = float('-inf')


def evaluate_depth(tree, src, parent):
    src_depth = 0

    for child in tree[src]:
        if child != parent:
            evaluate_depth(tree, child, src)
            src_depth = max(src_depth, 1 + depths[child])

    depths[src] = src_depth


def solve(tree, src, parent, parent_ans):
    '''
        For any generic node 'u' in the tree, there are 2 places where the farthest node could exist:
        1. In the subtree of 'u'. For this option, we just need to consider the depth of u

        2. Not in the subtree. This means the farthest node does not lie in the subtree. To calculate this, we first need to visit
           the parent, and then calculate the distance to farthest node from parent which is not inside the subtree region off 'u'
           We called this quantity max_p_without_u.

           Finally the ans for 'u' will be max(choice1, choice2)

           to calculate the max_p_without_u, there are 3 candidates.
            1. prefix max -> max depth among all children of p from 0 to u
            2. suffix_max -> max depth among all children of p from u+1 to k (considering p has k children)
            3. parent_ans -> parent ans of p (grandparent of u)

            take the max of all three and add 1. This will be the ans of choice 2

            calculate partial_ans and propagate it downwards.
    '''

    prefix_max = []
    suffix_max = []

    for child in tree[src]:
        if child != parent:
            prefix_max.append(depths[child])
            suffix_max.append(depths[child])

    for i in range(1, len(prefix_max)):
        prefix_max[i] = max(prefix_max[i], prefix_max[i - 1])

    for i in range(len(suffix_max) - 2, -1, -1):
        suffix_max[i] = max(suffix_max[i], suffix_max[i + 1])

    child_no = 0

    for child in tree[src]:
        if child != parent:
            # these are the depths among all nodes except u(whose ans we are calculating at the moment)
            max_depth_1 = MIN if child_no == 0 else prefix_max[child_no - 1]
            max_depth_2 = MIN if child_no == len(suffix_max) - 1 else suffix_max[child_no + 1]

            max_depth = max(max_depth_1, max_depth_2)
            # propagate this value to this child. this value is nothing but the value of farthest node from parent
            # which is outside of subtree rooted at u
            partial_ans = 1 + max(parent_ans, max_depth)

            solve(tree, child, src, partial_ans)

            child_no += 1

    # ans[src] = 1 + max(parent_ans, -1 if len(prefix_max) == 0 else prefix_max[-1])

    if len(prefix_max) == 0:
        # leaf node. In this case the parent ans will be the ans
        ans[src] = max(1 + parent_ans, 0)
    else:
        ans[src] = 1 + max(parent_ans, prefix_max[-1])


def main():
    n = int(input())
    tree = defaultdict(list)

    for i in range(0, n - 1):
        a, b = [int(x) for x in input().split()]
        tree[a].append(b)
        tree[b].append(a)

    evaluate_depth(tree, 1, 0)

    solve(tree, 1, 0, -1)

    for i in range(1, n + 1):
        print(ans[i], end=' ')


if __name__ == '__main__':
    main()
