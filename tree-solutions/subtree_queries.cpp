// https://cses.fi/problemset/task/1137
#include <iostream>
#include <vector>

#define SIZE 200005
#define ll long long

using namespace std;
int n, q, type, idx, value, a, b;
int timer;
vector<int> tree[SIZE];
int start[SIZE];
int endd[SIZE];
ll fenwick_tree[SIZE];
int values[SIZE];

ll query(int i)
{
    ll sum = 0;
    for (; i > 0; i -= (i & -i))
    {
        sum += fenwick_tree[i];
    }
    return sum;
}

void update(int i, int value)
{
    for (; i <= n; i += (i & -i))
    {
        fenwick_tree[i] += value;
    }
}

void dfs(int src, int parent)
{
    start[src] = ++timer;
    update(start[src], values[src]);

    for (int child : tree[src])
    {
        if (child != parent)
        {
            dfs(child, src);
        }
    }
    endd[src] = timer;
}

int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> values[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 0);

    while (q--)
    {
        cin >> type;
        if (type == 1)
        {
            cin >> idx >> value;
            update(start[idx], -values[idx]);
            values[idx] = value;
            update(start[idx], values[idx]);
        }
        else
        {
            cin >> idx;
            int left = start[idx] - 1;
            int right = endd[idx];
            cout << query(right) - query(left) << "\n";
        }
    }
}
