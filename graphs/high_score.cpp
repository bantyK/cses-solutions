// https://cses.fi/problemset/task/1673/
#include<iostream>
#include<vector>

using namespace std;
#define ll long long

const ll INF = 1e17;
const ll NINF = (-1) * INF;

struct edge {
    int src;
    int dest;
    ll distance;
};

int nodes, edges;
vector<edge> graph;
vector<ll> dist;

void bellman_ford() {
    for (int i = 1; i < nodes; i++) {
        //  nodes - 1 iterations

        for (auto e : graph) {
            int src = e.src;
            if (dist[src] == INF) continue;
            int destination = e.dest;
            ll d = e.distance;

            dist[destination] = min(dist[destination], dist[src] + d);
            // if the distance was initially -INF then the above line would change its value, which we dont want
            // hence the next line will bring it back to -INF.
            dist[destination] = max(dist[destination], NINF);
        }
    }

    // negative cycle detection. If there is a negative cycle then the distance will change after n - 1
    // relaxtions which happened above. If the distance changed, we will make that node as -INF

    for (int i = 1; i < nodes; i++) {
        //  nodes - 1 iterations

        for (auto e : graph) {
            int src = e.src;
            int destination = e.dest;
            ll d = e.distance;

            if (dist[src] == INF) continue;

            if (dist[destination] > dist[src] + d) {
                // distance changed, a relaxation happened
                dist[destination] = NINF;
            }
            // if the distance was initially -INF then the above line would change its value, which we dont want
            // hence the next line will bring it back to -INF.

        }
    }

}

/**
 * Perform Bellman Ford. If a negative cycle is found, return -1
 * else find the SSSP from 1 to n
 *
 * Negate the edges first, so that when we calculate the SSSP, we are actually calculating the SSLP
 * finally while returning, negate the distance again to print the correct result
 * @return
 */
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> nodes >> edges;

    dist.resize(nodes + 1);
    graph.resize(edges);

    for (int i = 0; i < edges; i++) {
        struct edge e{};
        cin >> e.src >> e.dest >> e.distance;
        e.distance *= -1; // to calculate the SSLP
        graph[i] = e;
    }
    dist[1] = 0;
    for (int i = 2; i <= nodes; i++) {
        dist[i] = INF;
    }

    bellman_ford();

    if (dist[nodes] == NINF) {
        cout << -1 << "\n";
    } else {
        // multiplied with -1 because we multiplied it before, in order to calculate SSLP instead of SSSP
        cout << -1 * dist[nodes] << "\n";
    }

    return 0;
}
