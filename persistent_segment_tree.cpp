// BOJ 11012 Egg

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Node {
    int val, left, right;
};

struct PersistentSegmentTree {
    vector<Node> tree;

    PersistentSegmentTree() { tree.push_back({0, 0, 0}); }

    int sum(int idx, int s, int e, int l, int r) {
        if (r < s || e < l)
            return 0;

        if (l <= s && e <= r)
            return tree[idx].val;

        int m = (s + e) >> 1;
        return sum(tree[idx].left, s, m, l, r) + sum(tree[idx].right, m + 1, e, l, r);
    }

    int update(int cur, int s, int e, int l, int k) {
        int nxt = tree.sz;
        tree.push_back({tree[cur].val + k, 0, 0});
        if (s == e)
            return nxt;

        int m = (s + e) >> 1;
        if (l <= m) {
            tree[nxt].left = update(tree[cur].left, s, m, l, k);
            tree[nxt].right = tree[cur].right;
        } else {
            tree[nxt].left = tree[cur].left;
            tree[nxt].right = update(tree[cur].right, m + 1, e, l, k);
        }

        return nxt;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m = 100001;

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<vector<int>> v(m + 1);
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;

            v[x + 1].push_back(y + 1);
        }

        vector<int> root(m + 1);
        PersistentSegmentTree pst;
        for (int x = 1; x <= m; x++) {
            root[x] = root[x - 1];

            for (int y : v[x])
                root[x] = pst.update(root[x], 1, m, y, 1);
        }

        ll ans = 0;
        while (q--) {
            int x, z, y, w;
            cin >> x >> z >> y >> w;

            ans += pst.sum(root[z + 1], 1, m, y + 1, w + 1);
            ans -= pst.sum(root[x], 1, m, y + 1, w + 1);
        }

        cout << ans << '\n';
    }
}
