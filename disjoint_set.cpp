// BOJ 1717 집합의 표현

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

    DisjointSet ds(n);
    ds.init();

    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;

        if (op == 1)
            cout << (ds.is_same(x, y) ? "YES" : "NO") << '\n';
        else
            ds.merge(x, y);
    }
}
