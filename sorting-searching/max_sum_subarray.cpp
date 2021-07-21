// https://cses.fi/problemset/task/1643/
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200005;
ll nums[N];

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    } 

    ll prev = nums[0];
    ll max_sum = nums[0];

    for(int i = 1; i < n; i++) {
        prev = max(nums[i], prev + nums[i]);
        max_sum = max(max_sum, prev);
    }

    cout << max_sum << "\n";
    return 0;
    
}