#include <iostream>
// https://cses.fi/problemset/task/1648/
#define ll long long
#define SZ 1000000

using namespace std;
ll n, q, a, b, idx, value;
int type;
ll nums[SZ];
ll segment_tree[SZ];

int getMid(ll s, ll e) {
    return s + (e - s) / 2;
}

ll build_segment_tree(ll s, ll e, ll si) {
    if (s == e) {
        segment_tree[si] = nums[s];
        return segment_tree[si];
    }

    int mid = getMid(s, e);

    ll left = build_segment_tree(s, mid, 2 * si + 1);
    ll right = build_segment_tree(mid + 1, e, 2 * si + 2);

    segment_tree[si] = left + right;
    return segment_tree[si];
}

ll rangeSum(ll qs, ll qe, ll ss, ll se, ll si) {
    if (ss >= qs && se <= qe) {
        // segment is completely inside the query, so use all of it
        // this whole segment is part of required sum
        return segment_tree[si];
    }

    if (ss > qe || qs > se) {
        return 0;
    }

    int mid = getMid(ss, se);

    ll left = rangeSum(qs, qe, ss, mid, 2 * si + 1);
    ll right = rangeSum(qs, qe, mid + 1, se, 2 * si + 2);
    return left + right;
}

void update(ll ss, ll se, ll pos, ll diff, ll si) {
    if (pos < ss || pos > se) {
        // the position is outside the segment, no update required
        return;
    }
    // all the segments which contains this position needs to be updated
    segment_tree[si] += diff;

    if (ss != se) {
        // if not leaf node, propagate this to children
        ll mid = getMid(ss, se);
        update(ss, mid, pos, diff, 2 * si + 1);
        update(mid + 1, se, pos, diff, 2 * si + 2);
    }
}


int main() {
    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    build_segment_tree(0, n - 1, 0);

    while (q--) {
        cin >> type;
        if (type == 1) {
            cin >> idx >> value;
            --idx;
            ll diff = value - nums[idx];
            nums[idx] = value;
            update(0, n - 1, idx, diff, 0);

        } else {
            cin >> a >> b;
            --a;
            --b;

            cout << rangeSum(a, b, 0, n - 1, 0) << "\n";
        }
    }

}
