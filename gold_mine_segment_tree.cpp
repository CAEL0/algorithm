// BOJ 10167 금광

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Node {
    ll mx, sum, left, right;
    Node() : mx(0), sum(0), left(0), right(0) {}
    Node(ll mx, ll sum, ll left, ll right) : mx(mx), sum(sum), left(left), right(right) {}
};

Node merge(Node a, Node b) {
    ll left = max(a.left, a.sum + b.left);
    ll right = max(b.right, a.right + b.sum);
    ll mx = max({a.mx, b.mx, left, right, a.right + b.left});
    return Node(mx, a.sum + b.sum, left, right);
}

struct SegmentTree {
    vector<Node> tree;

    SegmentTree(int n) { tree.resize(4 * n); }

    void clear() {
        for (int i = 0; i < tree.sz; i++)
            tree[i] = Node();
    }

    Node maximum(int idx, int s, int e, int l, int r) {
        if (r < s || e < l)
            return Node();

        if (l <= s && e <= r)
            return tree[idx];

        int m = (s + e) >> 1;
        return merge(maximum(2 * idx, s, m, l, r), maximum(2 * idx + 1, m + 1, e, l, r));
    }

    void update(int idx, int s, int e, int l, ll k) {
        if (l < s || e < l)
            return;

        if (s == e) {
            k += tree[idx].mx;
            tree[idx] = Node(k, k, k, k);
            return;
        }

        int m = (s + e) >> 1;
        update(2 * idx, s, m, l, k);
        update(2 * idx + 1, m + 1, e, l, k);
        tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    set<int> us;
    vector<pair<pii, int>> v(n);
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;

        us.insert(y);
        v[i] = make_pair(make_pair(x, y), z);
    }

    unordered_map<int, int> mp;
    int idx = 0;
    for (auto x : us)
        mp[x] = ++idx;

    for (int i = 0; i < n; i++)
        v[i].fi.se = mp[v[i].fi.se];

    sort(v.begin(), v.end());

    SegmentTree st(idx);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && v[i - 1].fi.fi == v[i].fi.fi)
            continue;

        st.clear();
        for (int j = i; j < n; j++) {
            st.update(1, 1, idx, v[j].fi.se, v[j].se);
            if (j == n - 1 || v[j].fi.fi != v[j + 1].fi.fi)
                ans = max(ans, st.maximum(1, 1, idx, 1, idx).mx);
        }
    }

    cout << ans;
}
