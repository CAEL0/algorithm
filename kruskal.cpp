// BOJ 1197 최소 스패닝 트리

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
    vector<int> dsu;

    DisjointSet(int _n) {
        n = _n;
        dsu.resize(n + 1);
    }

    void init() {
        for (int i = 1; i <= n; i++)
            dsu[i] = i;
    }

    int find(int z) {
        if (z != dsu[z])
            dsu[z] = find(dsu[z]);
        return dsu[z];
    }

    void merge(int x, int y) { dsu[find(y)] = find(x); }

    bool is_same(int x, int y) { return find(x) == find(y); }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<pair<pii, ll>> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].fi.fi >> edges[i].fi.se >> edges[i].se;

    sort(edges.begin(), edges.end(), [](auto &p, auto &q) { return p.se < q.se; });

    DisjointSet ds = DisjointSet(n);
    ds.init();

    ll ans = 0;
    int cnt = 0;

    for (auto &edge : edges) {
        if (ds.is_same(edge.fi.fi, edge.fi.se))
            continue;

        ds.merge(edge.fi.fi, edge.fi.se);
        ans += edge.se;

        if (++cnt == n - 1)
            break;
    }

    cout << ans;
}
