//https://cses.fi/problemset/task/1071
#include<iostream>

#define ll long long
using namespace std;

ll solve(ll r, ll c) {
    ll start, ans;
    if (r > c) {
        if (r % 2 == 0) {
            // r is even, decreasing sequence
            start = r * r;
            ans = start - (c - 1);
        } else {
            start = (r - 1) * (r - 1);
            start += 1;
            ans = start + (c - 1);
        }
    } else {
        // column value is greater
        if (c % 2 == 1) {
            // column is odd, decreasing sequence
            start = c * c;
            ans = start - (r - 1);
        } else {
            start = (c - 1) * (c - 1);
            start += 1;
            ans = start + (r - 1);
        }
    }
    return ans;
}

int main() {
    int t;
    cin >> t;
    ll r, c;
    while (t--) {
        cin >> r >> c;
        cout << solve(r, c) << "\n";
    }
}

