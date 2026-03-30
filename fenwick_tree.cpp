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

    void update(int l, ll k) {
        ll gap = k - sum(l, l);
        while (l <= n) {
            tree[l] += gap;
            l += (l & -l);
        }
    }

    void add(int l, ll k) {
        while (l <= n) {
            tree[l] += k;
            l += (l & -l);
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
        else if (op == 2)
            cout << ft.sum(x, y) << '\n';
    }
}
