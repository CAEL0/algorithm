// BOJ 2042 구간 합 구하기

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

    ll init(int idx, int s, int e, vector<ll> &v) {
        if (s == e)
            return tree[idx] = v[s];

        int m = (s + e) >> 1;
        return tree[idx] = init(2 * idx, s, m, v) + init(2 * idx + 1, m + 1, e, v);
    }

    ll sum(int idx, int s, int e, int l, int r) {
        if (r < s || e < l)
            return 0;

        if (l <= s && e <= r)
            return tree[idx];

        int m = (s + e) >> 1;
        return sum(2 * idx, s, m, l, r) + sum(2 * idx + 1, m + 1, e, l, r);
    }

    void update(int idx, int s, int e, int l, ll k) {
        if (l < s || e < l)
            return;

        if (s == e) {
            tree[idx] = k;
            return;
        }

        int m = (s + e) >> 1;
        if (l <= m)
            update(2 * idx, s, m, l, k);
        else
            update(2 * idx + 1, m + 1, e, l, k);

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
            ll x, k;
            cin >> x >> k;

            st.update(1, 1, n, x, k);
        } else if (op == 2) {
            int x, y;
            cin >> x >> y;

            cout << st.sum(1, 1, n, x, y) << '\n';
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

struct SegmentTree {
    int height, powh;
    vector<ll> tree;

    SegmentTree(int n) {
        height = ceil(log2(n));
        powh = 1 << height;
        tree.resize(2 * powh);
    }

    void init(vector<ll> &v) {
        for (int i = 0; i < v.sz; i++)
            tree[powh + i] = v[i];

        for (int h = height - 1; h >= 0; h--)
            for (int i = (1 << h); i < (1 << (h + 1)); i++)
                tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    ll sum(int l, int r) {
        l += powh - 1;
        r += powh - 1;

        ll ret = 0;
        while (l <= r) {
            if (l & 1) {
                ret += tree[l];
                l++;
            }

            if (!(r & 1)) {
                ret += tree[r];
                r--;
            }

            l >>= 1;
            r >>= 1;
        }

        return ret;
    }

    void update(int l, ll k) {
        l += powh - 1;
        ll gap = tree[l] - k;
        while (l) {
            tree[l] -= gap;
            l >>= 1;
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, p, q;
    cin >> n >> p >> q;

    vector<ll> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    SegmentTree st(n);
    st.init(v);

    q += p;
    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            ll x, k;
            cin >> x >> k;

            st.update(x, k);
        } else if (op == 2) {
            int x, y;
            cin >> x >> y;

            cout << st.sum(x, y) << '\n';
        }
    }
}
