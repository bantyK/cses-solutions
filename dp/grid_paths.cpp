// https://cses.fi/problemset/task/1638
#include<iostream>
#include<vector>
using namespace std;
const int mod = 1000000007;

void solve() {
    int n;
    cin >> n;
    
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<char>> input(n, vector<char>(n, 0));
    string row;
    for(int i = 0; i < n; i++) {
        cin >> row;
        for(int j = 0; j < n; j++) {
            if(row[j] == '*') {
                input[i][j] = '*';
            } else {
                input[i][j] = '.';
            }
        }
    }

    for(int i = 0; i < n; i++) {
        if(input[i][0] != '*') {
            dp[i][0] = 1;
        } else {
            break;
        }
    }

    for(int j = 0; j < n; j++) {
        if(input[0][j] != '*') {
            dp[0][j] = 1;
        } else {
            break;
        }
    }


    for(int i = 1; i < n; i++) {
        for(int j = 1; j < n; j++) {
            if(input[i][j] == '*') {
                dp[i][j] = 0;
            } else {
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
            }
        }
    }

    cout << dp[n - 1][n -1] << "\n";
}

void solve2() {
    int n;
    cin >> n;
    
    vector<vector<int>> dp(n, vector<int>(n, 0));
    dp[0][0] = 1;
    for(int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for(int j = 0; j < n; j++) {
            if(row[j] == '*') {
                dp[i][j] = 0;
            } else {
                if(i > 0) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
                }
                if(j > 0) {
                    dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
                }
            }
        }
    }
    cout << dp[n - 1][n -1] << "\n";
}

int main() {
    solve2();
}