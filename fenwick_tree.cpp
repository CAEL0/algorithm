// BOJ 2042 구간 합 구하기

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

    ll sum(int i) {
        ll ret = 0;
        while (i > 0) {
            ret += tree[i];
            i -= (i & -i);
        }
        return ret;
    }

    ll sum(int l, int r) { return sum(r) - sum(l - 1); }

    void update(int i, ll k) {
        ll gap = k - sum(i, i);
        while (i <= n) {
            tree[i] += gap;
            i += (i & -i);
        }
    }

    void add(int i, ll k) {
        while (i <= n) {
            tree[i] += k;
            i += (i & -i);
        }
    }

    ll kth(ll k) {
        int i = 1;
        while (i <= n)
            i <<= 1;

        ll ret = 0;
        while (i) {
            if (ret + i <= n && tree[ret + i] < k) {
                k -= tree[ret + i];
                ret += i;
            }
            i >>= 1;
        }
        return ret + 1;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, p, q;
    cin >> n >> p >> q;

    FenwickTree ft(n);
    for (int i = 1; i <= n; i++) {
        ll k;
        cin >> k;

        ft.update(i, k);
    }

    q += p;
    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            ll l, k;
            cin >> l >> k;

            ft.update(l, k);
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;

            cout << ft.sum(l, r) << '\n';
        }
    }
}
