#include<bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // sort(a.begin(), a.end());

    map<ll, int> index_map;

    for(int i = 0; i < n; i++) {
        ll compliment = k - a[i];

        if(index_map.find(compliment) != index_map.end()) {
            cout << index_map[compliment] + 1 << " " << i + 1    << "\n";
            return 0;
        }
        
        index_map[a[i]] = i;
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}