// BOJ 17474 수열과 쿼리 26

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Node {
    ll mx1, mx2, cnt, sum;
};

Node merge(Node a, Node b) {
    if (a.mx1 == b.mx1)
        return {a.mx1, max(a.mx2, b.mx2), a.cnt + b.cnt, a.sum + b.sum};

    if (a.mx1 > b.mx1)
        swap(a, b);

    return {b.mx1, max(a.mx1, b.mx2), b.cnt, a.sum + b.sum};
}

struct SegmentTreeBeats {
    vector<Node> tree;

    SegmentTreeBeats(int n) { tree.resize(4 * n); }

    Node init(int idx, int s, int e, vector<int> &v) {
        if (s == e)
            return tree[idx] = {v[s], -1, 1, v[s]};

        int m = (s + e) >> 1;
        return tree[idx] = merge(init(2 * idx, s, m, v), init(2 * idx + 1, m + 1, e, v));
    }

    void propagate(int idx, int s, int e) {
        if (s == e)
            return;

        for (int i = 2 * idx; i <= 2 * idx + 1; i++) {
            if (tree[idx].mx1 < tree[i].mx1) {
                tree[i].sum += tree[i].cnt * (tree[idx].mx1 - tree[i].mx1);
                tree[i].mx1 = tree[idx].mx1;
            }
        }
    }

    void update(int idx, int s, int e, int l, int r, int k) {
        propagate(idx, s, e);

        if (r < s || e < l || tree[idx].mx1 <= k)
            return;

        if (l <= s && e <= r && tree[idx].mx2 < k) {
            tree[idx].sum += tree[idx].cnt * (k - tree[idx].mx1);
            tree[idx].mx1 = k;
            propagate(idx, s, e);
            return;
        }

        int m = (s + e) >> 1;
        update(2 * idx, s, m, l, r, k);
        update(2 * idx + 1, m + 1, e, l, r, k);
        tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
    }

    int maximum(int idx, int s, int e, int l, int r) {
        propagate(idx, s, e);

        if (r < s || e < l)
            return 0;

        if (l <= s && e <= r)
            return tree[idx].mx1;

        int m = (s + e) >> 1;
        return max(maximum(2 * idx, s, m, l, r), maximum(2 * idx + 1, m + 1, e, l, r));
    }

    ll sum(int idx, int s, int e, int l, int r) {
        propagate(idx, s, e);

        if (r < s || e < l)
            return 0;

        if (l <= s && e <= r)
            return tree[idx].sum;

        int m = (s + e) >> 1;
        return sum(2 * idx, s, m, l, r) + sum(2 * idx + 1, m + 1, e, l, r);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    SegmentTreeBeats stb(n);
    stb.init(1, 1, n, v);

    int q;
    cin >> q;

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;

            stb.update(1, 1, n, l, r, k);
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;

            cout << stb.maximum(1, 1, n, l, r) << '\n';
        } else if (op == 3) {
            int l, r;
            cin >> l >> r;

            cout << stb.sum(1, 1, n, l, r) << '\n';
        }
    }
}
