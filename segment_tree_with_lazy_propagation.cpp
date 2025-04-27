// BOJ 10999 구간 합 구하기 2

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct SegmentTree {
    vector<ll> tree, lazy;

    SegmentTree(int n) {
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }

    ll init(int idx, int s, int e, vector<ll> &v) {
        if (s == e)
            return tree[idx] = v[s];

        int m = (s + e) >> 1;
        return tree[idx] = init(2 * idx, s, m, v) + init(2 * idx + 1, m + 1, e, v);
    }

    void propagate(int idx, int s, int e) {
        if (lazy[idx]) {
            if (s != e) {
                lazy[2 * idx] += lazy[idx];
                lazy[2 * idx + 1] += lazy[idx];
            }

            tree[idx] += (e - s + 1) * lazy[idx];
            lazy[idx] = 0;
        }
    }

    ll sum(int idx, int s, int e, int l, int r) {
        propagate(idx, s, e);

        if (r < s || e < l)
            return 0;

        if (l <= s && e <= r)
            return tree[idx];

        int m = (s + e) >> 1;
        return sum(2 * idx, s, m, l, r) + sum(2 * idx + 1, m + 1, e, l, r);
    }

    void update(int idx, int s, int e, int l, int r, ll k) {
        propagate(idx, s, e);

        if (r < s || e < l)
            return;

        if (l <= s && e <= r) {
            lazy[idx] = k;
            propagate(idx, s, e);
            return;
        }

        int m = (s + e) >> 1;
        update(2 * idx, s, m, l, r, k);
        update(2 * idx + 1, m + 1, e, l, r, k);
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, p, q;
    cin >> n >> p >> q;

    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    SegmentTree st(n);
    st.init(1, 1, n, v);

    q += p;
    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            ll x, y, k;
            cin >> x >> y >> k;

            st.update(1, 1, n, x, y, k);
        } else {
            int x, y;
            cin >> x >> y;

            cout << st.sum(1, 1, n, x, y) << '\n';
        }
    }
}
