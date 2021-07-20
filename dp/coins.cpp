//#include "functions.h"
//#include "util.h"
#include<iostream>
#include<vector>
#include <algorithm>
#include<cstring>
#include <string>
#include <unordered_map>
#define ll long long
#define mod 1000000007
#define inf (1LL<<60)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define loop(i,s,e) for(int i = s; i < e; ++i)
using namespace std;


void solve() {
    fast_io;
    int n;
    cin >> n;
    vector<double> probabilities(n);
    
    for(int i = 0; i < n; i++) {
        cin >> probabilities[i];
    }

    vector<vector<double>> dp(n + 1, vector<double>(n + 1, 0));
    //dp[i][j] = the probability to get j heads in i coin tosses

    dp[0][0] = 1; // probability to get 0 head when 0 coins are tossed is 1

    // dp[0] -> the probability to get 0 heads, meaning all tails
    
    for(int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] * (1 - probabilities[i-1]);
    }
    double res = 0;
    for(int i = n/2 + 1; i <= n; i++) {
        res += dp[n][i];
    }
    cout << res << endl;
}

int main(int argc, const char * argv[]) {
    solve();
    return 0;
}
