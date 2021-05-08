// https://cses.fi/problemset/task/1671
#include<bits/stdc++.h>
//#include<iostream>
//#include<vector>
//#include <queue>


using namespace std;
#define SZ 1000000
#define ll long long
#define mp make_pair
const ll MAX = 1e17;

vector<pair<int, int>> adj[SZ];
ll dist[SZ];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        dist[i] = MAX;
    }

    int a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        adj[a].emplace_back(mp(b, c));
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(mp(1, 0));
    dist[1] = 0;

    while (!pq.empty()) {
        int node = pq.top().first;
        ll distance_in_pq = pq.top().second;
        pq.pop();

        if (dist[node] < distance_in_pq) {
            continue;
        }

        for (auto child : adj[node]) {
            int to = child.first;
            ll distance = child.second;
            if (dist[to] > dist[node] + distance) {
                dist[to] = dist[node] + distance;
                pq.push({to, dist[to]});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    return 0;

}

