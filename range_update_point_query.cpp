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
        } else {
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

const int MAX = 100005;
int N, Q, A[MAX];
ll tree[MAX];

struct Fenwick {
    void init() {
        for (int k = 1; k <= N; k++)
            if (k + (k & -k) <= N)
                tree[k + (k & -k)] += tree[k];
    }
    void range(int k, ll v) {
        while (k < MAX) {
            tree[k] += v;
            k += (k & -k);
        }
    }
    void range(int l, int r, ll v) {
        range(l, v);
        range(r + 1, -v);
    }
    ll point(int k) {
        ll ret = 0;
        while (k > 0) {
            ret += tree[k];
            k -= (k & -k);
        }
        return ret;
    }
} fw;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        tree[i] = A[i] - A[i - 1];
    }
    fw.init();

    cin >> Q;
    while (Q--) {
        int q;
        cin >> q;
        if (q & 1) {
            int i, j, k;
            cin >> i >> j >> k;
            fw.range(i, k);
            fw.range(j + 1, -k);
        } else {
            int x;
            cin >> x;
            cout << fw.point(x) << '\n';
        }
    }
}
