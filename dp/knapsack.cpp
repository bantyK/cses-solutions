//#include "functions.h"
//#include "util.h"
#include<iostream>
#include<vector>
#include <algorithm>
#include<cstring>
#define ll long long
#define mod 1000000007
#define inf (1LL<<60)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define loop(i,s,e) for(int i = s; i < e; ++i)
using namespace std;

void solve() {
    fast_io;
    int n, w;
    cin >> n >> w;
    vector<vector<int>> arr(n, vector<int>(2));
    
    for(int i = 0; i < n; i++) {
        cin >> arr[i][0] >> arr[i][1];
    }
    
    vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0));
    dp[0][0] = 1;
    
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= w; j++) {
            dp[i][j] = dp[i-1][j];
            int remaining = j - arr[i][0];
            if(remaining > 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][remaining]);
            }
        }
    }
    
    cout << dp[n][w] << endl;
}

int main(int argc, const char * argv[]) {
    solve();
    return 0;
}
