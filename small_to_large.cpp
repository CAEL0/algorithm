// BOJ 17469 트리의 색깔과 쿼리

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
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> parent(n + 1);
    for (int i = 2; i <= n; i++)
        cin >> parent[i];

    vector<unordered_set<int>> colors(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        colors[i].insert(x);
    }

    q += n - 1;
    vector<pii> query(q);

    for (int i = 0; i < q; i++)
        cin >> query[i].fi >> query[i].se;

    DisjointSet ds(n);
    ds.init();

    vector<int> ans;

    for (int i = q - 1; i >= 0; i--) {
        auto [op, x] = query[i];

        if (op == 1) {
            int y = ds.find(parent[x]);
            x = ds.find(x);

            if (colors[x].sz < colors[y].sz)
                swap(x, y);

            ds.dsu[y] = x;

            for (int z : colors[y])
                colors[x].insert(z);
        } else
            ans.push_back(colors[ds.find(x)].sz);
    }

    for (int i = ans.sz - 1; i >= 0; i--)
        cout << ans[i] << '\n';
}
