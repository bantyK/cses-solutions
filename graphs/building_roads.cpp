// https://cses.fi/problemset/result/2073611/
#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define mp make_pair
#define f first
#define s second

int cities, num_roads;
vector<ii > roads;
int parents[100001];

// disjoint set methods
bool anUnion(int i, int j);

int find(int x);

int main() {
    cin >> cities >> num_roads;

    for (int i = 1; i <= cities; i++) {
        parents[i] = i;
    }
    int a, b;
    for (int i = 0; i < num_roads; i++) {
        cin >> a >> b;
        roads.emplace_back(mp(a, b));
    }
    int disjoints = cities;

    for (ii road : roads) {
        anUnion(road.f, road.s);
        --disjoints;
    }

    if (disjoints == 1) {
        cout << 0;
        return 0;
    }
    vector<ii > new_roads;

    for (int j = 2; j <= cities; j++) {
        if (anUnion(1, j)) {
            disjoints--;
            new_roads.emplace_back(mp(1, j));
        }
        if (disjoints == 1) {
            break;
        }
    }

    cout << new_roads.size() << "\n";
    for (ii road : new_roads) {
        cout << road.f << " " << road.s << "\n";
    }

    return 0;
}

bool anUnion(int i, int j) {
    int parentI = find(i);
    int parentJ = find(j);

    if (parentI == parentJ) {
        return false;
    }

    parents[parentJ] = parents[parentI];
    return true;
}

int find(int x) {
    if (parents[x] == x) {
        return x;
    }
    return parents[x] = find(parents[x]);
}
