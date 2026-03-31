// BOJ 16975 수열과 쿼리 21

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct SegmentTree {
    vector<ll> tree;

    SegmentTree(int n) { tree.resize(4 * n); }

    void init(int idx, int s, int e, vector<ll> &v) {
        if (s == e) {
            tree[idx] = v[s];
            return;
        }

        int m = (s + e) >> 1;
        init(2 * idx, s, m, v);
        init(2 * idx + 1, m + 1, e, v);
    }

    void range(int idx, int s, int e, int l, int r, ll k) {
        if (r < s || e < l)
            return;

        if (l <= s && e <= r) {
            tree[idx] += k;
            return;
        }

        int m = (s + e) >> 1;
        range(2 * idx, s, m, l, r, k);
        range(2 * idx + 1, m + 1, e, l, r, k);
    }

    ll point(int idx, int s, int e, int l) {
        if (l < s || e < l)
            return 0;

        if (s == e)
            return tree[idx];

        int m = (s + e) >> 1;
        if (l <= m)
            return tree[idx] + point(2 * idx, s, m, l);

        return tree[idx] + point(2 * idx + 1, m + 1, e, l);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    SegmentTree st(n);
    st.init(1, 1, n, v);

    int q;
    cin >> q;

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;

            st.range(1, 1, n, l, r, k);
        } else if (op == 2) {
            int l;
            cin >> l;

            cout << st.point(1, 1, n, l) << '\n';
        }
    }
}
