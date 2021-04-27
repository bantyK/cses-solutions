// https://cses.fi/problemset/task/1647/
#include <iostream>

# define ll long long
#define SZ 1000000

using namespace std;
ll n, q,a, b;
ll segment_tree[SZ];
ll nums[SZ];
const ll inf = 1LL << 62;

ll build_segment_tree(ll start, ll end, ll segmentTreeIndex) {
    if (start == end) {
        segment_tree[segmentTreeIndex] = nums[start];
        return segment_tree[segmentTreeIndex];
    }

    ll mid = start + (end - start) / 2;

    ll left = build_segment_tree(start, mid, 2 * segmentTreeIndex + 1);
    ll right = build_segment_tree(mid + 1, end, 2 * segmentTreeIndex + 2);

    segment_tree[segmentTreeIndex] = min(left, right);
    return segment_tree[segmentTreeIndex];
}

ll query(ll segmentStart, ll segmentEnd, ll queryStart, ll queryEnd, ll segmentIndex) {
    if (segmentStart >= queryStart && segmentEnd <= queryEnd) {
        // segment is completely inside the query, this segment will be completely used for this query
        return segment_tree[segmentIndex];
    }
    // segment completely outside the query
    if (segmentStart > queryEnd || queryStart > segmentEnd) {
        return inf;
    }

    ll mid = segmentStart + (segmentEnd - segmentStart) / 2;

    return min(
            query(segmentStart, mid, queryStart, queryEnd, 2 * segmentIndex + 1),
            query(mid + 1, segmentEnd, queryStart, queryEnd, 2 * segmentIndex + 2)
    );
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    build_segment_tree(0, n - 1, 0);

    while (q--) {
        cin >> a >> b;
        --a;
        --b;
        cout << query(0, n - 1, a, b, 0) << "\n";
    }
    return 0;
}