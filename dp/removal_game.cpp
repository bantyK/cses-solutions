// https://cses.fi/problemset/task/1097/
#include<iostream>
#include<vector>
#define ll long long
#define mod 1000000007;

using namespace std;


void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    
    // gap method, finding all smaller subproblems before we
    // calculate bigger subproblems
    for(int len = 1; len <= n; len++) {
        for(int i = 0; i + len <= n; i++) {
            int j = i + len - 1; // this is the right limit

            // these are the steps which is left after player 2 is done with his chance    
            // If player 2 plays optimally, than he would make sure that the next chance that 
            // player 1 gets will get the minimum possible value which is possible to get from
            // the next chance. 

            // So while considering player 1's next move, we should consider the minimum value
            ll x = (i + 2 <= j) ? dp[i + 2][j] : 0; // player 1 and player 2 picks i, i + 1 stones
            ll y = (i + 1 <= j - 1) ?dp[i + 1][j - 1] : 0; // player 1 picks 1 and player 2 picks j
            ll z = (i <= j - 2) ? dp[i][j - 2] : 0; // player 1 and player 2 picks j, j - 2 stones
            
            dp[i][j] = max(arr[i] + min(x, y), arr[j] + min(y, z));
        }
    }
    
    cout << dp[0][n - 1] << "\n"; // whole string
    
}

int main() {
    solve();
}