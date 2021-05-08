//https://cses.fi/problemset/task/1672
#include<iostream>

using namespace std;

#define ll long long

ll adj[500][500];
int n, m, q;
ll INF = 1e15;

void floyd_warshall() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // edge relaxation
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
}

int main() {
    cin >> n >> m >> q;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) adj[i][j] = 0;
            else adj[i][j] = INF;
        }
    }


    ll a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        adj[a][b] = adj[b][a] = min(c, adj[a][b]);
    }

    floyd_warshall();

    while (q--) {
        cin >> a >> b;
        if (adj[a][b] == INF)
            adj[a][b] = -1;

        cout << adj[a][b] << "\n";;

    }
}