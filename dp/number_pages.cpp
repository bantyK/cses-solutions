//https://cses.fi/problemset/task/1158
#include<iostream>
#include<vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> prices(n, 0);    
    vector<int> pages(n, 0);    
    for(int i = 0; i < n; i++) {
        cin >> prices[i];
    }

    for(int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    vector<vector<int>> dp(n, vector<int>(x + 1, 0));

    for(int i = 0; i < n; i++) {
        dp[i][0] = 0; // first col represent no money, so we can't make any profit
    }

    for(int j = 0; j <= x; j++) {
        if(prices[0] <= j) {
            dp[0][j] = pages[0];
        }
    }

    for(int i = 1; i < n; i++) { // books
        for(int j = 1; j <= x; j++) { // remaining amount
            dp[i][j] = dp[i - 1][j];
            if(prices[i] <= j) {
                dp[i][j] = max(dp[i][j], pages[i] + dp[i - 1][j - prices[i]]);
            }
        }
    }

    cout << dp[n-1][x] << "\n";
}