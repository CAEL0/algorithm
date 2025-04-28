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

    FenwickTree(int _n) {
        n = _n;
        tree.resize(n + 1);
    }

    ll sum(int k) {
        ll ret = 0;
        while (k > 0) {
            ret += tree[k];
            k -= (k & -k);
        }

        return ret;
    }

    ll sum(int l, int r) { return sum(r) - sum(l - 1); }

    ll kth(ll k) {
        ll idx = 1;
        while (idx <= n)
            idx <<= 1;

        ll ret = 0;
        while (idx) {
            if (ret + idx <= n && tree[ret + idx] < k) {
                k -= tree[ret + idx];
                ret += idx;
            }

            idx >>= 1;
        }

        return ret + 1;
    }

    void update(int k, ll v) {
        ll gap = v - sum(k, k);
        while (k <= n) {
            tree[k] += gap;
            k += (k & -k);
        }
    }

    void add(int k, ll v) {
        while (k <= n) {
            tree[k] += v;
            k += (k & -k);
        }
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
        ll x;
        cin >> x;

        ft.update(i, x);
    }

    q += p;
    while (q--) {
        ll op, x, y;
        cin >> op >> x >> y;

        if (op == 1)
            ft.update(x, y);
        else
            cout << ft.sum(x, y) << '\n';
    }
}
