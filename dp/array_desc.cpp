#include <iostream>
#include <vector>
#include<cstring>
using namespace std;


const int mod = 1000000007;

int solve(vector<int> arr, int n, int max) {
    int dp[n][max + 1];
    memset(dp, 0, sizeof dp);

    // First row -> base case
    // If there is only one element in the array
    for(int j = 1; j <= max; j++) {
        if(arr[0] == 0 || arr[0] == j) {
            dp[0][j] = 1;
        }
    }

    /*
    
        dp[i][v] = total number of ways to fill the array up to index i, if x[i] = v.

        if the array[i] contains some other number than j, then that is not a valid array because I 
        cannot replace an existing number in the array

        if the array[i] already contains j, than that is a valid array and we will consider that

        if I am at position i, and if array[0: i - 1] is a valid array and array[i - 1] contains one of 
        these 3 values:

        j + 1, j - 1, j

        than we can extend arr[0 : i - 1] to arr[0: i] and arr[0 : i] will be a valid array

    */

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= max; j++) {
            dp[i][j] = 0;
            if (arr[i] == 0 || arr[i] == j) {
                int a = (dp[i - 1][j - 1] + dp[i - 1][j]) % mod;
                int b = j + 1 <= max ? (dp[i - 1][j + 1] % mod) : 0; // avoiding out of bound
                dp[i][j] = (a + b) % mod;
            }
        }
    }

    /*
        Our answer is dp[N]
        we need count of all possible valid arrays by filling all possible numbers
        from 1 to max.

        Hence we sum all the values 
    */
    int totalCount = 0;
    for(int j = 1; j <= max; j++) {
        totalCount = (totalCount + dp[n - 1][j]) % mod;
    }
    return totalCount;

}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }


    cout << solve(arr, n, m) << "\n";
}