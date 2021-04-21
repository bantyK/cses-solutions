// https://cses.fi/problemset/task/1688
#include <bits/stdc++.h>

using namespace std;

vector<int> tree[200001];
int level[200001];
int up[200001][20];

void dfs(int src, int parent)
{
    level[src] = 1 + level[parent];

    up[src][0] = parent;

    for (int i = 1; i < 20; i++)
    {
        int prev_parent = up[src][i - 1]; // node at a position 2 * (i - 1) level higher than src
        if (prev_parent == -1)
            up[src][i] = -1;
        else
            up[src][i] = up[prev_parent][i - 1]; // node at a position 2 * (i - 1) level higher than prev_parent
    }

    for (int child : tree[src])
    {
        if (parent != child)
        {
            dfs(child, src);
        }
    }
}

// a should be at a level deeper than b
int lca(int a, int b)
{
    // a should be at deeper level than b
    if (level[a] < level[b])
    {
        int temp = a;
        a = b;
        b = temp;
    }

    // find the ancestor of a which is at same level as b
    int diff = level[a] - level[b];
    for (int i = 19; i >= 0; --i)
    {
        if (level[a] - (1 << i) >= level[b])
        {
            a = up[a][i];
        }
    }

    // if b is the ancestor of a, then b is the LCA
    if (a == b)
    {
        return b;
    }

    for (int i = 19; i >= 0; i--)
    {
        // if the parent's of a and b are not same.
        // travel up
        if (up[a][i] != up[b][i])
        {
            a = up[a][i];
            b = up[b][i];
        }
    }

    return up[a][0]; // at this state a and b are just below their LCA
}

int main()
{
    int n, q;
    cin >> n >> q;

    int parent;
    for (int i = 2; i <= n; i++)
    {
        cin >> parent;

        tree[i].push_back(parent);
        tree[parent].push_back(i);
    }
    level[1] = 0;

    dfs(1, -1);

    int a, b;

    while (q--)
    {

        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
}