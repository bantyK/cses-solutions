// https://cses.fi/problemset/task/1633/
#include<iostream>
#include<vector>

using namespace std;

#define ll long long
#define MOD 1000000007

int main() {
	int n;
	cin >> n;
	vector<ll> dp(n+1, 0);
	dp[0] = 1;
	
	for(int i = 1; i <= n; i++) {
		for(int roll = 1; roll <= 6; roll++) {
			if(roll <= i) {
				dp[i] = (dp[i] + dp[i - roll]) % MOD;
			}
		}
	}
	cout << dp[n] << "\n";
}
