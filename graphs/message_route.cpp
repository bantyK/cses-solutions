// https://cses.fi/problemset/task/1667/
#include<iostream>
#include <vector>
#include<queue>
#include <algorithm>

#define mp make_pair
#define SZ 1000000
using namespace std;
int n, m;
vector<int> graph[SZ];
bool visited[SZ];
int parent[SZ];

void print_path(int node);

int main() {
    cin >> n >> m;
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    queue<pair<int, int>> queue;
    queue.push(mp(1, 1));
    visited[1] = true;


    while (!queue.empty()) {
        pair<int, int> curr = queue.front();
        queue.pop();
        if (curr.first == n) {
            cout << curr.second << "\n";
            print_path(n);
            return 0;
        }


        for (int child : graph[curr.first]) {
            if (!visited[child]) {
                visited[child] = true;
                queue.push(mp(child, curr.second + 1));
                parent[child] = curr.first;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}

void print_path(int node) {
    vector<int> path;
    while (node != 1) {
        path.push_back(node);
        node = parent[node];
    }

    reverse(path.begin(), path.end());

    cout << 1 << " ";
    for (int p : path) {
        cout << p << " ";
    }
}

