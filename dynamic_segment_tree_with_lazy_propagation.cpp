// BOJ 20212 나무는 쿼리를 싫어해~

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
    ll lazy = 0;
};

struct SegmentTree {
    int j = 1;
    vector<Node> tree;

    SegmentTree() { tree.resize(4000000); }

    void propagate(int idx, int s, int e) {
        if (idx == -1 || tree[idx].lazy == 0)
            return;

        tree[idx].sum += tree[idx].lazy * (e - s + 1);
        if (s != e) {
            if (tree[idx].left == -1)
                tree[idx].left = ++j;

            tree[tree[idx].left].lazy += tree[idx].lazy;

            if (tree[idx].right == -1)
                tree[idx].right = ++j;

            tree[tree[idx].right].lazy += tree[idx].lazy;
        }

        tree[idx].lazy = 0;
    }

    ll sum(int idx, int s, int e, int l, int r) {
        propagate(idx, s, e);

        if (idx == -1 || r < s || e < l)
            return 0;

        if (l <= s && e <= r)
            return tree[idx].sum;

        int m = (s + e) >> 1;
        return sum(tree[idx].left, s, m, l, r) + sum(tree[idx].right, m + 1, e, l, r);
    }

    void update(int idx, int s, int e, int l, int r, ll k) {
        propagate(idx, s, e);

        if (idx == -1 || r < s || e < l)
            return;

        if (l <= s && e <= r) {
            tree[idx].lazy = k;
            propagate(idx, s, e);
            return;
        }

        if (tree[idx].left == -1)
            tree[idx].left = ++j;

        if (tree[idx].right == -1)
            tree[idx].right = ++j;

        ll m = (s + e) >> 1;
        update(tree[idx].left, s, m, l, r, k);
        update(tree[idx].right, m + 1, e, l, r, k);

        tree[idx].sum = 0;
        if (tree[idx].left != -1)
            tree[idx].sum += tree[tree[idx].left].sum;

        if (tree[idx].right != -1)
            tree[idx].sum += tree[tree[idx].right].sum;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int q;
    cin >> q;

    vector<pair<pii, int>> v;
    vector<pair<pii, pii>> w;
    for (int l = 0; l < q; l++) {
        int op, i, j, k;
        cin >> op >> i >> j >> k;

        if (op == 1)
            v.push_back(make_pair(make_pair(i, j), k));
        else if (op == 2)
            w.push_back(make_pair(make_pair(k, l), make_pair(i, j)));
    }

    sort(w.begin(), w.end());

    int j = 0;
    int mx = 1e9 + 5;
    SegmentTree st;
    vector<pair<int, ll>> ans(w.sz);
    for (int i = 0; i < w.sz; i++) {
        ans[i].fi = w[i].fi.se;

        while (j < w[i].fi.fi) {
            st.update(1, 1, mx, v[j].fi.fi, v[j].fi.se, v[j].se);
            j++;
        }

        ans[i].se = st.sum(1, 1, mx, w[i].se.fi, w[i].se.se);
    }

    sort(ans.begin(), ans.end());

    for (int i = 0; i < ans.sz; i++)
        cout << ans[i].se << '\n';
}
