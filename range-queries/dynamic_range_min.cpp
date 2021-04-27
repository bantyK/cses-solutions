#include <iostream>
// https://cses.fi/problemset/task/1649
using namespace std;
#define SZ 1000000
#define ll long long
const ll inf = 1LL << 62;
ll n, q, a, b, i, value;
int type;
ll segment_tree[SZ];
ll nums[SZ];

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
    segment_tree[si] = min(left, right);
    return segment_tree[si];
}

ll range_min(ll qs, ll qe, ll ss, ll se, ll si) {
    if (ss >= qs && se <= qe) {
        return segment_tree[si];
    }
    if (ss > qe || se < qs) {
        return inf;
    }

    ll mid = getMid(ss, se);
    ll left = range_min(qs, qe, ss, mid, 2 * si + 1);
    ll right = range_min(qs, qe, mid + 1, se, 2 * si + 2);
    return min(left, right);
}

void update(ll idx, ll val, ll s, ll e, ll si) {
    if (s == e) {
        nums[s] = val;
        segment_tree[si] = val;
        return;
    }

    ll mid = getMid(s, e);
    if (idx >= s && idx <= mid) {
        // go left
        update(idx, val, s, mid, 2 * si + 1);
    } else {
        // go right
        update(idx, val, mid + 1, e, 2 * si + 2);
    }
    segment_tree[si] = min(segment_tree[2 * si + 1], segment_tree[2 * si + 2]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;

    for (ll i = 0; i < n; i++) {
        cin >> nums[i];
    }

    build_segment_tree(0, n - 1, 0);

    while (q--) {
        cin >> type;
        if (type == 1) {
            cin >> i >> value;
            i--;
            update(i, value, 0, n - 1, 0);
        } else {
            cin >> a >> b;
            --a;
            --b;

            cout << range_min(a, b, 0, n - 1, 0) << "\n";
        }
    }


    return 0;
}