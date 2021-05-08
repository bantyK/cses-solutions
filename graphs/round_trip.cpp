// https://cses.fi/problemset/task/1669/
#include<bits/stdc++.h>

#define SZ 1000000
using namespace std;
int n, m;
bool visited[SZ];
vector<int> adj[SZ]; // adjacency list
unordered_map<int, int> parent_map;
int cycle_start_point, cycle_end_point;

// return true if a cycle is found
bool dfs(int src, int parent) {
    visited[src] = true;
    parent_map[src] = parent;

    for (int child : adj[src]) {
        if (child == parent) continue;
        if (visited[child]) {
            // there is a cycle
            cycle_start_point = child;
            cycle_end_point = src;
            return true;
        }
        if (!visited[child]) {
            if (dfs(child, src)) return true;
        }
    }

    return false;
}

void printPath() {
    int curr = cycle_end_point;
    vector<int> path;
    path.emplace_back(cycle_end_point);

    while (curr != cycle_start_point) {
        path.emplace_back(parent_map[curr]);
        curr = parent_map[curr];
    }
    path.emplace_back(cycle_end_point);

    cout << path.size() << "\n";

    for (int i : path) {
        cout << i << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    int a, b;

    for (int i = 1; i <= n; i++) visited[i] = false;

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (dfs(i, -1)) {
                printPath();
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}