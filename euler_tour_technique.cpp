// BOJ 2820 자동차 공장

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct SegmentTree {
    vector<ll> tree;

    SegmentTree(int n) { tree.resize(4 * n); }

    void init(int idx, int s, int e, vector<ll> &v) {
        if (s == e) {
            tree[idx] = v[s];
            return;
        }

        int m = (s + e) >> 1;
        init(2 * idx, s, m, v);
        init(2 * idx + 1, m + 1, e, v);
    }

    ll point(int idx, int s, int e, int l) {
        if (l < s || e < l)
            return 0;

        if (s == e)
            return tree[idx];

        int m = (s + e) >> 1;
        return tree[idx] + point(2 * idx, s, m, l) + point(2 * idx + 1, m + 1, e, l);
    }

    void range(int idx, int s, int e, int l, int r, ll x) {
        if (r < s || e < l)
            return;

        if (l <= s && e <= r) {
            tree[idx] += x;
            return;
        }
        int m = (s + e) >> 1;
        range(2 * idx, s, m, l, r, x);
        range(2 * idx + 1, m + 1, e, l, r, x);
    }
};

void dfs(int cur, vector<vector<int>> &graph, int &idx, vector<int> &in, vector<int> &out) {
    in[cur] = ++idx;
    for (int nxt : graph[cur])
        dfs(nxt, graph, idx, in, out);

    out[cur] = idx;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> v(n + 1);
    vector<vector<int>> graph(n + 1);

    cin >> v[1];
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> v[i] >> p;

        graph[p].push_back(i);
    }

    int idx = 0;
    vector<int> in(n + 1);
    vector<int> out(n + 1);
    dfs(1, graph, idx, in, out);

    SegmentTree st(n);

    while (q--) {
        char op;
        cin >> op;

        if (op == 'p') {
            int a, x;
            cin >> a >> x;

            st.range(1, 1, n, in[a] + 1, out[a], x);
        } else {
            int a;
            cin >> a;

            cout << st.point(1, 1, n, in[a]) + v[a] << '\n';
        }
    }
}
