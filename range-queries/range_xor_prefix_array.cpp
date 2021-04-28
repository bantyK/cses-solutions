#include<iostream>
// https://cses.fi/problemset/task/1650/
#define ll long long
using namespace std;
#define MAX 200005

ll nums[MAX];
ll n, q, a, b;

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}

void solve() {
    cin >> n >> q;
    nums[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        nums[i] ^= nums[i - 1];
    }

    while (q--) {
        cin >> a >> b;
        cout << (nums[b] xor nums[a - 1]) << "\n";
    }
}

