// https://cses.fi/problemset/task/1668/
// Graph bipartite
#include <iostream>

using namespace std;

#include<vector>

int n, m, a, b;
#define SZ 1000000
vector<int> graph[SZ];
int color[SZ];

bool dfs(int src, int currentColor) {
    color[src] = currentColor;
    for (int child : graph[src]) {
        if (color[child] == -1) {
            int nextColor = currentColor == 1 ? 2 : 1;
            if (!dfs(child, nextColor)) return false;
        } else {
            if (color[child] == currentColor) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        color[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            bool possible = dfs(i, 1);
            if (!possible) {
                cout << "IMPOSSIBLE";
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << color[i] << " ";
    }
}