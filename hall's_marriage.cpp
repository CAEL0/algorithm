// BOJ 8177 Ice Skates

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

    Node init(int idx, int s, int e, ll k) {
        if (s == e)
            return tree[idx] = Node(k, k, k, k);

        int m = (s + e) >> 1;
        return tree[idx] = merge(init(2 * idx, s, m, k), init(2 * idx + 1, m + 1, e, k));
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
        if (l <= m)
            update(2 * idx, s, m, l, k);
        else
            update(2 * idx + 1, m + 1, e, l, k);

        tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n, q, k, d;
    cin >> n >> q >> k >> d;

    SegmentTree st(n - d);
    st.init(1, 1, n - d, -k);

    ll kd = k * d;
    while (q--) {
        ll r, x;
        cin >> r >> x;

        if (x)
            st.update(1, 1, n - d, r, x);

        cout << (st.tree[1].mx <= kd ? "TAK" : "NIE") << '\n';
    }
}
