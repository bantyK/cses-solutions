//https://cses.fi/problemset/task/1634/

#include<iostream>
#include<vector>
#define ll long long
#define INF 10000000

using namespace std;
int coins[100];

int main() {
	int n, total;
	cin >> n >> total;
	int coins[n];
	for(int i = 0; i < n; i++) {
		cin >> coins[i];
	}
	vector<ll> dp(total + 1, INF);
	
	dp[0] = 0;
	
	// for(int i = 0; i < (int)dp.size(); i++) cout << dp[i] << " ";
	

	for(int i = 1; i <= total; i++) {
		for(int j = 0; j < n; j++) {
			if(coins[j] <= i) {
				dp[i] = min(dp[i], 1 + dp[i - coins[j]]);
			}
		}
	}

	ll res = dp[total] == INF ? -1 : dp[total];
	cout << res << "\n";
}