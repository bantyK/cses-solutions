#include<iostream>

#define ll long long

using namespace std;
ll nums[200005];
ll prefix_sum[200005];
int n, q;

void calculate_prefix_sum() {
    prefix_sum[1] = nums[1];
    for (int i = 2; i <= n; i++) {
        prefix_sum[i] = nums[i] + prefix_sum[i - 1];
    }
}

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    calculate_prefix_sum();
    int a, b;
    while (q--) {
        cin >> a >> b;
        cout << prefix_sum[b] - prefix_sum[a - 1] << "\n";
    }
}
