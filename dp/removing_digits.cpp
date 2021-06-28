// https://cses.fi/problemset/task/1637
#include<iostream>
#include<vector>
#include<climits>
#include<unordered_set>
using namespace std;

int main() {
    int n;
    cin >> n;
    if(n < 10) {
        cout << 1 << "\n";
        return 0;
    }

    vector<int> dp(n + 1, INT_MAX);

    for(int i = 1; i < 10; i++) {
        dp[i] = 1;
    }

    for(int i = 10; i <= n; i++) {
        for(int digit : to_string(i)) {
            if(digit > 0) {
                dp[i] = min(dp[i], 1 + dp[i - (digit - '0')]);
            }
        }
    }
    cout << dp[n] << "\n";
}


