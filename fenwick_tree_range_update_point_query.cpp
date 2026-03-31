// BOJ 16975 수열과 쿼리 21

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct FenwickTree {
    int n;
    vector<ll> tree;

    FenwickTree(int n) : n(n) { tree.resize(n + 1); }

    void range(int i, ll k) {
        while (i <= n) {
            tree[i] += k;
            i += (i & -i);
        }
    }

    void range(int l, int r, ll k) {
        range(l, k);
        range(r + 1, -k);
    }

    ll point(int i) {
        ll ret = 0;
        while (i > 0) {
            ret += tree[i];
            i -= (i & -i);
        }
        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    FenwickTree ft(n);
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;

        ft.range(i, i, k);
    }

    int q;
    cin >> q;

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;

            ft.range(l, r, k);
        } else if (op == 2) {
            int l;
            cin >> l;

            cout << ft.point(l) << '\n';
        }
    }
}
