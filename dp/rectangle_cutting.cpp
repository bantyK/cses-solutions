// https://cses.fi/problemset/task/1744/
#include<iostream>
#include<vector>
using namespace std;

void solve() {
    int length, height;
    cin >> length >> height;
    // dp[W][H] => min number of cuts required to make the rectangle of dim W x H into squares
    vector<vector<int>> dp(height + 1, vector<int>(length + 1));
    
    for(int i = 0; i <= height; i++) {
        for(int j = 0; j <= length; j++) {
            if(j == i) {
                // if the length and height of the rectangle is same than it is already a square,
                // no cuts required
                dp[i][j] = 0;
            } else {
                dp[i][j] = 1e9;
                // we can make horizontal cuts or vertical cuts
                
                // horizontal cuts
                // when we make a horizontal cut, the rectangle is basically divided into 2 rentangles
                // lets say the cut is made at level k, we now have 2 rectangles of following dimension
                // length remains same if we make horizontal cuts
                // 1. length = l, height = k
                // 2, length = l, height = h - k 
                // here h and k are the dimension of original rectangle before cutting (we will check this for
                // the entire rectangle so i and j will go from 0 to length and 0 to height)
                for(int k = 1; k < i; k++) {
                    dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
                }
                
                // vertical cuts

                // Similar to horizontal cuts, when we make vertical cuts, we again divide the rectangle into 2 halves
                // height remains same if we make vertical cuts
                // length = k, height = h [0 to k]
                // length = l - k, height = h [k + 1 to l]

                for(int k = 1; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
                }

                // the smaller cuts that we generate after cutting the rectangles are smaller subsets of
                // the same problem which we have already solved
            }
        }
    }
    
    cout << dp[height][length] << "\n";       
}

int main() {
    solve();
}


