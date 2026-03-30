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
        init();
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

struct Kruskal {
    int n;
    vector<pair<pii, int>> edges;

    Kruskal(int n, vector<pair<pii, int>> edges) : n(n), edges(edges) {}

    ll minimum_spanning_tree() {
        sort(edges.begin(), edges.end(), [](pair<pii, int> p, pair<pii, int> q) { return p.se < q.se; });

        DisjointSet ds(n);
        ll ret = 0;
        int cnt = 0;
        for (pair<pii, int> p : edges) {
            if (ds.is_same(p.fi.fi, p.fi.se))
                continue;

            ds.merge(p.fi.fi, p.fi.se);
            ret += p.se;

            cnt++;
            if (cnt == n - 1)
                break;
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<pair<pii, int>> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].fi.fi >> edges[i].fi.se >> edges[i].se;

    Kruskal kruskal(n, edges);

    cout << kruskal.minimum_spanning_tree();
}
