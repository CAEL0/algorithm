// BOJ 14577 일기예보

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Node {
    int left = -1;
    int right = -1;
    ll sum = 0;
};

struct SegmentTree {
    int j = 1;
    vector<Node> tree;

    SegmentTree() { tree.resize(4000000); }

    ll sum(int idx, ll s, ll e, ll l, ll r) {
        if (idx == -1 || r < s || e < l)
            return 0;

        if (l <= s && e <= r)
            return tree[idx].sum;

        ll m = (s + e) >> 1;
        return sum(tree[idx].left, s, m, l, r) + sum(tree[idx].right, m + 1, e, l, r);
    }

    void update(int idx, ll s, ll e, ll l, ll k) {
        if (s == e) {
            tree[idx].sum += k;
            return;
        }

        ll m = (s + e) >> 1;
        if (l <= m) {
            if (tree[idx].left == -1)
                tree[idx].left = ++j;

            update(tree[idx].left, s, m, l, k);
        } else {
            if (tree[idx].right == -1)
                tree[idx].right = ++j;

            update(tree[idx].right, m + 1, e, l, k);
        }

        tree[idx].sum = 0;
        if (tree[idx].left != -1)
            tree[idx].sum += tree[tree[idx].left].sum;

        if (tree[idx].right != -1)
            tree[idx].sum += tree[tree[idx].right].sum;
    }

    ll kth(int idx, ll s, ll e, ll k) {
        if (s == e)
            return s;

        ll m = (s + e) >> 1;
        if (tree[idx].left == -1)
            return kth(tree[idx].right, m + 1, e, k);

        if (tree[idx].right == -1)
            return kth(tree[idx].left, s, m, k);

        if (k <= tree[tree[idx].left].sum)
            return kth(tree[idx].left, s, m, k);

        return kth(tree[idx].right, m + 1, e, k - tree[tree[idx].left].sum);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll mx = 1e18 + 5;

    int n, q;
    cin >> n >> q;

    SegmentTree st;
    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];

        st.update(1, 1, mx, v[i] + 1, 1);
    }

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            ll i, x;
            cin >> i >> x;

            st.update(1, 1, mx, v[i] + 1, -1);
            v[i] += x;
            st.update(1, 1, mx, v[i] + 1, 1);
        } else if (op == 2) {
            ll i, x;
            cin >> i >> x;

            st.update(1, 1, mx, v[i] + 1, -1);
            v[i] -= x;
            st.update(1, 1, mx, v[i] + 1, 1);
        } else if (op == 3) {
            ll l, r;
            cin >> l >> r;

            cout << st.sum(1, 1, mx, l + 1, r + 1) << '\n';
        } else if (op == 4) {
            ll k;
            cin >> k;

            cout << st.kth(1, 1, mx, n + 1 - k) - 1 << '\n';
        }
    }
}
