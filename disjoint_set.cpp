// BOJ 1717 집합의 표현

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 1000005;

struct DisjointSet {
    int n, dsu[MAX], rnk[MAX];

    DisjointSet(int n) { this->n = n; }

    void init() {
        for (int i = 1; i <= n; i++) {
            dsu[i] = i;
            rnk[i] = 1;
        }
    }

    int find(int z) {
        if (z != dsu[z])
            dsu[z] = find(dsu[z]);
        return dsu[z];
    }

    void uni(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return;

        if (rnk[x] < rnk[y])
            swap(x, y);

        rnk[x] += rnk[y];
        dsu[y] = x;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    DisjointSet ds = DisjointSet(n);
    ds.init();

    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
            cout << (ds.find(x) == ds.find(y) ? "YES" : "NO") << '\n';
        else
            ds.uni(x, y);
    }
}
