// https://cses.fi/problemset/task/1639/
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string n, m;
    cin >> n >> m;
    int len1 = n.length();
    int len2 = m.length();

    // dp[i][j] -> edit distance with string1 ending at index i and string2 ending at index j
    int dp[len1 + 1][len2 + 1];
    dp[0][0] = 0;

    // first row, only string2 exist, string1 is empty
    for (int j = 1; j <= len2; j++)
    {
        dp[0][j] = 1 + dp[0][j - 1];
    }

    // first column, only string1 exist, string2 is empty
    for (int i = 1; i <= len1; i++)
    {
        dp[i][0] = 1 + dp[i - 1][0];
    }

    for(int i = 1; i <= len1; i++) {
        for(int j = 1; j <= len2; j++) {
            if(n[i - 1] == m[j - 1]) {
                // if the characters at index i and j are same, then we dont have to calculate
                // anything, the edit distance between them is same as whatever the
                // distance distance was when these 2 chars are not added
                dp[i][j] = dp[i-1][j-1];
            } else {
                // if the characters are not same, then in this case 
                // i can add a character into string2, remove a character from string2 or replace 
                // a character in string 2
                // out of these 3 operations, whichever gives the minimum edit distance, we will
                // take that and add 1 because we performed one operation
                int addition = dp[i - 1][j];
                int deletion = dp[i][j - 1];
                int replace = dp[i - 1][j - 1];

                dp[i][j] = 1 + min(min(addition, deletion), replace);
            }
        }
    }
    cout << dp [len1][len2] << "\n";
}