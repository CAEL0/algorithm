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

    ll point(int idx, int s, int e, int l) {
        if (l < s || e < l)
            return 0;

        if (s == e)
            return tree[idx];

        int m = (s + e) >> 1;
        return tree[idx] + point(2 * idx, s, m, l) + point(2 * idx + 1, m + 1, e, l);
    }

    void range(int idx, int s, int e, int l, int r, ll x) {
        if (r < s || e < l)
            return;

        if (l <= s && e <= r) {
            tree[idx] += x;
            return;
        }
        
        int m = (s + e) >> 1;
        range(2 * idx, s, m, l, r, x);
        range(2 * idx + 1, m + 1, e, l, r, x);
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

    SegmentTree st = SegmentTree(n);
    st.init(1, 1, n, v);

    int q;
    cin >> q;

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            ll l, r, x;
            cin >> l >> r >> x;

            st.range(1, 1, n, l, r, x);
        } else if (op == 2) {
            int l;
            cin >> l;

            cout << st.point(1, 1, n, l) << '\n';
        }
    }
}

//--------------------------------------------------------------------------------

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct FenwickTree {
    int n;
    vector<ll> tree;

    FenwickTree(int _n) {
        n = _n;
        tree.resize(n + 1);
    }

    void init(vector<int> &v) {
        for (int i = 1; i <= n; i++)
            tree[i] = v[i] - v[i - 1];

        for (int idx = 1; idx <= n; idx++)
            if (idx + (idx & -idx) <= n)
                tree[idx + (idx & -idx)] += tree[idx];
    }

    ll point(int idx) {
        ll ret = 0;
        while (idx > 0) {
            ret += tree[idx];
            idx -= (idx & -idx);
        }

        return ret;
    }

    void range(int idx, ll k) {
        while (idx <= n) {
            tree[idx] += k;
            idx += (idx & -idx);
        }
    }

    void range(int l, int r, ll k) {
        range(l, k);
        range(r + 1, -k);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    FenwickTree ft(n);
    ft.init(v);

    int q;
    cin >> q;

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;

            ft.range(l, r, k);
        } else if (op == 2) {
            int l;
            cin >> l;

            cout << ft.point(l) << '\n';
        }
    }
}
