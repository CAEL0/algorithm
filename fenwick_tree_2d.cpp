// BOJ 11658 구간 합 구하기 3

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct FenwickTree2D {
    int n;
    vector<vector<ll>> tree;

    FenwickTree2D(int n) : n(n) { tree.resize(n + 1, vector<ll>(n + 1)); }

    ll sum(int i, int j) {
        ll ret = 0;
        int ii = i;
        while (j > 0) {
            while (i > 0) {
                ret += tree[i][j];
                i -= (i & -i);
            }
            j -= (j & -j);
            i = ii;
        }
        return ret;
    }

    void update(int i, int j, ll k) {
        int ii = i;
        while (j <= n) {
            while (i <= n) {
                tree[i][j] += k;
                i += (i & -i);
            }
            j += (j & -j);
            i = ii;
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    FenwickTree2D ft(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int k;
            cin >> k;

            ft.update(i, j, k);
        }
    }

    while (q--) {
        int op;
        cin >> op;

        if (op == 0) {
            int x, y, k;
            cin >> x >> y >> k;

            k -= ft.sum(x, y);
            k += ft.sum(x - 1, y);
            k += ft.sum(x, y - 1);
            k -= ft.sum(x - 1, y - 1);

            ft.update(x, y, k);
        } else if (op == 1) {
            int x, y, z, w;
            cin >> x >> y >> z >> w;

            cout << ft.sum(z, w) - ft.sum(x - 1, w) - ft.sum(z, y - 1) + ft.sum(x - 1, y - 1) << '\n';
        }
    }
}
