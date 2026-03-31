// BOJ 15646 농부 후안은 바리스타입니다

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct FenwickTree2D {
    int n, m;
    vector<vector<ll>> tree;

    FenwickTree2D(int n, int m) : n(n), m(m) { tree.resize(n + 1, vector<ll>(m + 1)); }

    void range(int i, int j, ll k) {
        int ii = i;
        while (j > 0) {
            while (i > 0) {
                tree[i][j] += k;
                i -= (i & -i);
            }
            j -= (j & -j);
            i = ii;
        }
    }

    ll point(int i, int j) {
        ll ret = 0;
        int ii = i;
        while (j <= m) {
            while (i <= n) {
                ret += tree[i][j];
                i += (i & -i);
            }
            j += (j & -j);
            i = ii;
        }
        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, q;
    cin >> n >> m >> q;

    FenwickTree2D ft(n, m);
    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x, y, z, w, k;
            cin >> x >> y >> z >> w >> k;

            ft.range(z, w, k);
            ft.range(x - 1, w, -k);
            ft.range(z, y - 1, -k);
            ft.range(x - 1, y - 1, k);
        } else if (op == 2) {
            int x, y;
            cin >> x >> y;

            cout << ft.point(x, y) << '\n';
        }
    }
}
