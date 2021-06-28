// https://cses.fi/problemset/task/1635
#include<iostream>
#include<vector>
using namespace std;

const int mod = 1000000007;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> coins(n);
    for(int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    int dp[x + 1];
    dp[0] = 1;

    for(int i = 1; i <= x; i++) {
        dp[i] = 0;
        for(int coin : coins) {
            if(coin <= i) {
                dp[i] = (dp[i] + dp[i - coin]) % mod;
            }
        }
    }

    cout << dp[x];
}