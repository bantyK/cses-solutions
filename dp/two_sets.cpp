// https://cses.fi/problemset/task/1093/
#include <iostream>
#include <vector>
#define ll long long
#define mod 1000000007;
#define loop(x, n) for (int x = 0; x < n; ++x)
using namespace std;

void solve()
{
    int n;
    cin >> n;
    int target = n * (n + 1) / 2;

    if (target % 2)
    {
        cout << 0 << "\n";
        return;
    }

    target /= 2;

    // total number of ways to make the sum = amount by using the numbers in array
    // [1, n]

    vector<vector<ll>> dp(n + 1, vector<ll>(target + 1, 0));
    dp[0][0] = 1;
    // we have to make sure that we keep atleast 1 element for the second set
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= target; j++)
        {
            dp[i][j] = dp[i - 1][j]; // not choosing the current number
            // if I choose the current number, this is the remaining amount that remains
            int remaining = j - i;
            if (remaining >= 0)
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - i]) % mod;
            }
        }
    }

    cout << dp[n - 1][target] << "\n";
}

int main()
{
    solve();
}