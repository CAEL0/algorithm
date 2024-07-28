// BOJ 13510 트리와 쿼리 1

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct SegmentTree {
    vector<int> tree;

    SegmentTree(int n) { tree.resize(4 * n); }

    int init(int idx, int s, int e, vector<int> &v) {
        if (s == e)
            return tree[idx] = v[s];

        int m = (s + e) >> 1;
        return tree[idx] = max(init(2 * idx, s, m, v), init(2 * idx + 1, m + 1, e, v));
    }

    int maximum(int idx, int s, int e, int l, int r) {
        if (r < s || e < l)
            return 0;

        if (l <= s && e <= r)
            return tree[idx];

        int m = (s + e) >> 1;
        return max(maximum(2 * idx, s, m, l, r), maximum(2 * idx + 1, m + 1, e, l, r));
    }

    void update(int idx, int s, int e, int l, int k) {
        if (l < s || e < l)
            return;

        if (s == e) {
            tree[idx] = k;
            return;
        }

        int m = (s + e) >> 1;
        update(2 * idx, s, m, l, k);
        update(2 * idx + 1, m + 1, e, l, k);
        tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
    }
};

void dfs1(int cur, vector<vector<pii>> &graph, vector<int> &parent, vector<int> &sub, vector<int> &depth) {
    sub[cur] = 1;

    for (pii &nxt : graph[cur]) {
        if (sub[nxt.fi])
            continue;

        parent[nxt.fi] = cur;
        depth[nxt.fi] = depth[cur] + 1;

        dfs1(nxt.fi, graph, parent, sub, depth);
        sub[cur] += sub[nxt.fi];

        if (sub[graph[cur][0].fi] < sub[nxt.fi])
            swap(graph[cur][0], nxt);
    }
}

void dfs2(int cur, vector<vector<pii>> &graph, vector<int> &parent, vector<int> &weight, vector<int> &top, vector<int> &in, vector<int> &out, int &idx) {
    in[cur] = ++idx;

    for (pii &nxt : graph[cur]) {
        if (nxt.fi == parent[cur])
            continue;

        if (nxt.fi == graph[cur][0].fi)
            top[nxt.fi] = top[cur];
        else
            top[nxt.fi] = nxt.fi;

        dfs2(nxt.fi, graph, parent, weight, top, in, out, idx);
        weight[in[nxt.fi]] = nxt.se;
    }

    out[cur] = idx;
}

int query(int a, int b, vector<int> &parent, vector<int> &depth, vector<int> &top, vector<int> &in, SegmentTree &st, int n) {
    int ret = 0;

    while (top[a] != top[b]) {
        if (depth[top[a]] > depth[top[b]])
            swap(a, b);

        ret = max(ret, st.maximum(1, 1, n, in[top[b]], in[b]));
        b = parent[top[b]];
    }

    if (depth[a] > depth[b])
        swap(a, b);

    return max(ret, st.maximum(1, 1, n, in[a] + 1, in[b]));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pii> edges(n);
    vector<vector<pii>> graph(n + 1);

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        edges[i] = {u, v};
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<int> parent(n + 1);
    vector<int> sub(n + 1);
    vector<int> depth(n + 1);

    dfs1(1, graph, parent, sub, depth);

    vector<int> weight(n + 1);
    vector<int> top(n + 1);
    vector<int> in(n + 1);
    vector<int> out(n + 1);
    top[1] = 1;
    int idx = 0;

    dfs2(1, graph, parent, weight, top, in, out, idx);

    SegmentTree st(n);
    st.init(1, 1, n, weight);

    int q;
    cin >> q;

    while (q--) {
        int op, u, v;
        cin >> op >> u >> v;

        if (op == 1) {
            int lower = (depth[edges[u].fi] > depth[edges[u].se] ? edges[u].fi : edges[u].se);
            st.update(1, 1, n, in[lower], v);
        } else
            cout << query(u, v, parent, depth, top, in, st, n) << '\n';
    }
}
