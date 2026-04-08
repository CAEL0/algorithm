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
    vector<int> dsu, rank;

    DisjointSet(int _n) {
        n = _n;
        dsu.resize(n + 1);
        rank.resize(n + 1);
        init();
    }

    void init() {
        for (int i = 1; i <= n; i++) {
            dsu[i] = i;
            rank[i] = 1;
        }
    }

    int find(int z) {
        if (z != dsu[z])
            dsu[z] = find(dsu[z]);
        return dsu[z];
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return;

        if (rank[x] < rank[y])
            swap(x, y);

        rank[x] += rank[y];
        dsu[y] = x;
    }

    bool is_same(int x, int y) { return find(x) == find(y); }
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
        int op = query[i].fi;
        int x = query[i].se;

        if (op == 1) {
            int y = ds.find(parent[x]);
            x = ds.find(x);

            if (colors[x].sz < colors[y].sz)
                swap(x, y);

            ds.dsu[y] = x;
            for (int z : colors[y])
                colors[x].insert(z);
        } else if (op == 2)
            ans.push_back(colors[ds.find(x)].sz);
    }

    for (int i = ans.sz - 1; i >= 0; i--)
        cout << ans[i] << '\n';
}
