//https://cses.fi/problemset/task/1145/
#include<iostream>
#include<vector>
#define ll long long
#define mod 1000000007;
#define loop(i,s,e) for(int i = s; i < e; ++i)
using namespace std;

int bs(vector<int> buckets, int value) {
    int low = 0;
    int high = (int)buckets.size();
    while(low < high) {
        int mid = low + (high - low) / 2;
        if(buckets[mid] >= value) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}
void solve() {
    int n;
    cin >> n;
    int arr[n];
    loop(i, 0, n) cin >> arr[i];
    vector<int> buckets;
    buckets.push_back(arr[0]);
    for(int i = 1; i < n; i++) {
        if(arr[i] > buckets[(int) buckets.size() - 1]) {
            // this element is largest than all the existing buckets
            buckets.push_back(arr[i]);
        } else {
            // find the left most bucket where this element could sit
            int idx = bs(buckets,arr[i]);
            buckets[idx] = arr[i];
        }
    }
    cout << (int) buckets.size() << "\n";
    
}


int main()
{
    solve();
}


