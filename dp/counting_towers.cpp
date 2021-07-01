#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_map>
using namespace std;
#define ll long long
#define mod 1000000007;

using namespace std;
int main()
{
    int t;
    cin >> t;
    unordered_map<int, int> cache;
    while (t--)
    {
        int n;
        cin >> n;

        if(cache.count(n) > 0) {
            cout << cache[n] << "\n";
            continue;
        }
        vector<vector<int>> dp(n + 2, vector<int>(2, 0)); // linked or unlinked. 0 is unlinked tiles and 1 is linked tiles

        dp[n + 1][0] = dp[n + 1][1] = 1; // number of ways to make an empty level (n to n + 1) is 1

        for (int i = n; i >= 2; i--)
        {
            // not extending any of the previous tile, hence I have an option to put either 2x1 or 2 * 1x1 tiles.
            ll op1 = (dp[i + 1][0] + dp[i + 1][1]) % mod;

            // if the tiles at below tiles are not linked, and I have extended both of these, then at here also
            // I have the same option. I have an unlinked tile situation at i + 1 also
            ll op2 = dp[i + 1][0];

            // extending any one of the tiles.
            ll op3 = (2 * dp[i + 1][0]) % mod;

            // extending a linked tile. In this case at my next level I am going to have a linked tile.
            ll op4 = dp[i + 1][1];

            dp[i][0] = (op1 + op2 + op3) % mod;
            dp[i][1] = (op1 + op4) % mod;
        }
        ll res = (dp[2][0] + dp[2][1]) % mod;
        cache[n] = res;
        cout << res << "\n";
    }
}