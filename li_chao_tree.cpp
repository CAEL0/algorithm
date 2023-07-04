// BOJ 12795 반평면 땅따먹기

#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()
#define bk back()

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Line {
    ll a, b;
    ll val(ll x) { return a * x + b; }
};

struct Node {
    int l, r;
    ll s, e;
    Line line;
};

struct Li_Chao {
    vector<Node> tree;

    void init() {
        tree.push_back({-1, -1, (ll)-2e12, (ll)2e12, {0, (ll)-2e18}});
    }
    ll maximum(int idx, ll x) {
        if (idx == -1)
            return LLONG_MIN;

        ll ret = tree[idx].line.val(x);
        if (x <= (tree[idx].s + tree[idx].e) / 2)
            ret = max(ret, maximum(tree[idx].l, x));
        else
            ret = max(ret, maximum(tree[idx].r, x));
        return ret;
    }
    void update(int idx, Line line) {
        ll s = tree[idx].s;
        ll e = tree[idx].e;
        Line lo = tree[idx].line;
        Line hi = line;

        if (lo.val(s) > hi.val(s))
            swap(lo, hi);

        if (lo.val(e) <= hi.val(e)) {
            tree[idx].line = hi;
            return;
        }
        ll m = (s + e) >> 1;
        if (lo.val(m) < hi.val(m)) {
            tree[idx].line = hi;
            if (tree[idx].r == -1) {
                tree[idx].r = tree.sz;
                tree.push_back({-1, -1, m + 1, e, lo});
            } else
                update(tree[idx].r, lo);
        } else {
            tree[idx].line = lo;
            if (tree[idx].l == -1) {
                tree[idx].l = tree.sz;
                tree.push_back({-1, -1, s, m, hi});
            } else
                update(tree[idx].l, hi);
        }
    }
} li_chao;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    li_chao.init();

    int q;
    cin >> q;

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            ll a, b;
            cin >> a >> b;

            li_chao.update(0, {a, b});
        } else if (op == 2) {
            ll x;
            cin >> x;

            cout << li_chao.maximum(0, x) << '\n';
        }
    }
}
