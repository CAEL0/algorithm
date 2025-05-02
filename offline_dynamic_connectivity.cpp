// BOJ 16911 그래프와 쿼리

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct DisjointSet {
    int n;
    vector<int> dsu, rank;
    vector<pair<pii, int>> v;

    DisjointSet(int _n) {
        n = _n;
        dsu.resize(n + 1);
        rank.resize(n + 1);
    }

    void init() {
        for (int i = 1; i <= n; i++) {
            dsu[i] = i;
            rank[i] = 1;
        }
    }

    int find(int z) {
        if (z == dsu[z])
            return z;
        return find(dsu[z]);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;

        if (rank[x] < rank[y])
            swap(x, y);

        dsu[y] = x;

        if (rank[x] == rank[y]) {
            rank[x]++;
            v.push_back(make_pair(make_pair(x, y), 1));
        } else
            v.push_back(make_pair(make_pair(x, y), 0));

        return true;
    }

    void rollback(int cnt) {
        while (cnt--) {
            auto [p, k] = v.bk;
            v.pop_back();

            dsu[p.se] = p.se;
            rank[p.fi] -= k;
        }
    }

    bool is_same(int x, int y) { return find(x) == find(y); }
};

void update(int idx, int s, int e, int l, int r, pii p, vector<vector<pii>> &tree) {
    if (r < s || e < l)
        return;

    if (l <= s && e <= r) {
        tree[idx].push_back(p);
        return;
    }

    int m = (s + e) >> 1;
    update(2 * idx, s, m, l, r, p, tree);
    update(2 * idx + 1, m + 1, e, l, r, p, tree);
}

void solve(int idx, int s, int e, vector<pair<pii, int>> &queries, vector<int> &convert, vector<vector<pii>> &tree, DisjointSet &ds, vector<int> &ans) {
    int cnt = 0;
    for (pii p : tree[idx])
        cnt += ds.merge(p.fi, p.se);

    if (s == e) {
        ans[s] = ds.is_same(queries[convert[s]].fi.fi, queries[convert[s]].fi.se);
        ds.rollback(cnt);
        return;
    }

    int m = (s + e) >> 1;
    solve(2 * idx, s, m, queries, convert, tree, ds, ans);
    solve(2 * idx + 1, m + 1, e, queries, convert, tree, ds, ans);

    ds.rollback(cnt);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<pair<pii, int>> queries(q);
    vector<int> convert(q);
    int k = 0;
    for (int i = 0; i < q; i++) {
        int op, x, y;
        cin >> op >> x >> y;

        queries[i] = make_pair(make_pair(min(x, y), max(x, y)), op);
        if (op == 3)
            convert[++k] = i;
    }

    int t = 1;
    map<pii, int> mp;
    vector<vector<pii>> tree(4 * k);
    for (int i = 0; i < q; i++) {
        auto [p, op] = queries[i];

        if (op == 1)
            mp[p] = t;
        else if (op == 2) {
            update(1, 1, k, mp[p], t - 1, p, tree);
            mp.erase(p);
        } else if (op == 3)
            t++;
    }

    for (auto [p, tt] : mp)
        update(1, 1, k, tt, t - 1, p, tree);

    DisjointSet ds(n);
    ds.init();

    vector<int> ans(k + 1);
    solve(1, 1, k, queries, convert, tree, ds, ans);

    for (int i = 1; i <= k; i++)
        cout << ans[i] << '\n';
}
