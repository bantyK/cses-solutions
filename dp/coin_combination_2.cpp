// https://cses.fi/problemset/task/1636
#include <iostream>
#include <vector>
#define ll long long
using namespace std;
const int mod = 1000000007;

int main() {
    int n, x;
    cin >> n >> x;
    
    vector<int> coins(n);
    for(int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    
    vector<vector<int>> dp(n, vector<int>(x + 1));
    
    for (int j = 1; j <= x; j++) {
        dp[0][j] = 0;
    }

    for(int i = 0; i < n; i++) {
        dp[i][0] = 1;
    }


    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= x; j++) {
            dp[i][j] = 0;

            if(i > 0)
                dp[i][j] = dp[i-1][j]; // not choosing   

            if(coins[i] <= j) {
                dp[i][j] = (dp[i][j] + dp[i][j - coins[i]]) % mod; // choosing
            }
        }
    }

    cout << dp[n - 1][x] <<"\n";

}