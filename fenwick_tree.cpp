// BOJ 2042 구간 합 구하기

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 1000005;

struct FenwickTree {
    int n;
    ll tree[MAX];

    FenwickTree(int n) { this->n = n; }

    ll summation(int k) {
        ll ret = 0;
        while (k > 0) {
            ret += tree[k];
            k -= (k & -k);
        }
        return ret;
    }

    ll summation(int l, int r) { return summation(r) - summation(l - 1); }

    ll kth(ll k) {
        ll ret = 0;
        ll idx = 1;
        while (idx <= n)
            idx *= 2;

        while (idx) {
            if (ret + idx <= n && tree[ret + idx] < k) {
                k -= tree[ret + idx];
                ret += idx;
            }
            idx /= 2;
        }
        return ret + 1;
    }

    void update(int k, ll v) {
        ll gap = v - summation(k, k);
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

    FenwickTree ft = FenwickTree(n);

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
            cout << ft.summation(x, y) << '\n';
    }
}
