// https://cses.fi/problemset/submit/1136/
#include <iostream>
#include<vector>

using namespace std;

vector<int> tree[200001];
int level[200001];
int up[200001][20];
int values[200001];

void dfs(int src, int parent) {
    level[src] = 1 + level[parent];
    up[src][0] = parent;
    for (int i = 1; i < 20; ++i) {
        int prev_parent = up[src][i - 1];
        if (prev_parent == -1) up[src][i] = -1;
        else up[src][i] = up[prev_parent][i - 1];
    }

    for (int child : tree[src]) {
        if (parent != child) {
            dfs(child, src);
        }
    }
}

int lca(int a, int b) {
    if (level[a] < level[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    for (int i = 19; i >= 0; i--) {
        if (level[a] - (1 << i) >= level[b]) {
            a = up[a][i];
        }
    }

    if (a == b) return a;

    for (int i = 19; i >= 0; i--) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

int dfs_for_ans(int src, int parent) {
    int x = values[src];
    for(int child : tree[src]) {
        if(parent != child) {
            x += dfs_for_ans(child, src);
        }
    }
    values[src] = x;
    return x;
}

int main() {
    int n, q;
    cin >> n >> q;
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, -1);

    while (q--) {
        cin >> a >> b;
        int w = lca(a, b);
        values[a] += 1;
        values[b] += 1;
        values[w] -= 1;
        int parent_lca = up[w][0];
        if (parent_lca != -1) {
            values[parent_lca] -= 1;
        }
    }

    dfs_for_ans(1, -1);

    for(int i = 1; i <= n; i++) {
        cout << values[i] << " ";
    }

    return 0;
}
