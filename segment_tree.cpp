//BOJ 2042 구간 합 구하기

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
        update(2 * idx, s, m, l, k);
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
        ll op, x, y;
        cin >> op >> x >> y;

        if (op == 1)
            st.update(1, 1, n, x, y);
        else
            cout << st.sum(1, 1, n, x, y) << '\n';
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

int powh;
ll tree[3000010];

ll summation(int a, int b) {
    ll ret = 0;
    a += powh - 1;
    b += powh - 1;
    while (a <= b) {
        if (a & 1)
            ret += tree[a++];
        if (!(b & 1))
            ret += tree[b--];
        a >>= 1;
        b >>= 1;
    }
    return ret;
}
void update(int k, ll c) {
    int idx = powh + k - 1;
    ll gap = tree[idx] - c;
    while (idx) {
        tree[idx] -= gap;
        idx >>= 1;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, x, y;
    cin >> n >> x >> y;

    int height = ceil(log2(n));
    powh = pow(2, height);

    for (int i = 0; i < n; i++)
        cin >> tree[powh + i];
    
    for (int h = height - 1; h >= 0; h--)
        for (int i = pow(2, h); i < pow(2, h + 1); i++)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    
    for (int i = 0; i < x + y; i++) {
        ll p, q, r;
        cin >> p >> q >> r;
        if (p == 1)
            update(q, r);
        else
            cout << add(q, r) << '\n';
    }
}
