//https://cses.fi/problemset/task/1745/
#include<iostream>
#include<vector>
#define mod 1000000007;

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> coins(n);
    int total = 0;
    for(int i = 0; i < n; i++) {
        cin >> coins[i];
        total += coins[i];
    }
    
    // classical 0/1 knapsack problem
    // dp[i][x] -> true if it is possible to make the amount x by using the first i coins.
    vector<vector<bool>> dp(n + 1, vector<bool>(total + 1, false));
    
    dp[0][0] = true;
    
    for(int i = 1; i <= n; i++) {
        for(int amount = 0; amount <= total; amount++) {
            dp[i][amount] = dp[i - 1][amount]; // not choosing the coin at current index
            
            // choosing the coin at current index
            int remainingAmount = amount - coins[i - 1];
            if(remainingAmount >= 0 && dp[i-1][remainingAmount]) {
                dp[i][amount] = true;
            }
        }
    }
    
    vector<int> possible;
    for(int i = 1; i <= total; i++) {
        if(dp[n][i]) {
            possible.push_back(i);
        }
    }
    
    cout << possible.size() << "\n";
    for(int i = 0; i < (int)possible.size(); i++) {
        cout << possible[i] << " ";
    }   
}

int main() {
    solve();
}