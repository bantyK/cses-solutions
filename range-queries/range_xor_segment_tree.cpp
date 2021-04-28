#include<iostream>
// https://cses.fi/problemset/task/1650
using namespace std;

#define ll long long
#define SZ 1000000
const ll inf = 1LL << 62;
ll nums[SZ];
ll segment_tree[SZ];
ll n, q, a, b;

ll getMid(ll s, ll e) {
    return s + (e - s) / 2;
}

ll build_segment_tree(ll s, ll e, ll si) {
    if (s == e) {
        segment_tree[si] = nums[s];
        return segment_tree[si];
    }
    ll mid = getMid(s, e);
    ll left = build_segment_tree(s, mid, 2 * si + 1);
    ll right = build_segment_tree(mid + 1, e, 2 * si + 2);

    segment_tree[si] = (left ^ right);
    return segment_tree[si];
}

ll query(ll qs, ll qe, ll ss, ll se, ll si) {
    if (ss >= qs && se <= qe) {
        return segment_tree[si];
    }

    if (qs > se || ss > qe) {
        return 0;
    }

    ll m = getMid(ss, se);

    return (query(qs, qe, ss, m, 2 * si + 1) ^ query(qs, qe, m + 1, se, 2 * si + 2));
}

int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    build_segment_tree(0, n - 1, 0);

    while (q--) {
        cin >> a >> b;
        cout << query(--a, --b, 0, n - 1, 0) << "\n";
    }
    return 0;
}
