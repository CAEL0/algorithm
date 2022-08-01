// BOJ 13510 트리와 쿼리 1

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 100005;
int N, Q, idx, par[MAX], sub[MAX], dep[MAX], weight[MAX], in[MAX], out[MAX], top[MAX], tree[4 * MAX];
pii edges[MAX];
struct Edge {
    int nxt, w;
};
vector<Edge> graph[MAX];

void dfs1(int cur) {
    sub[cur] = 1;
    for (auto &edge: graph[cur]) {
        if (!sub[edge.nxt]) {
            par[edge.nxt] = cur;
            dep[edge.nxt] = dep[cur] + 1;
            dfs1(edge.nxt);
            sub[cur] += sub[edge.nxt];
            if (sub[graph[cur][0].nxt] < sub[edge.nxt])
                swap(graph[cur][0], edge);
        }
    }
}
void dfs2(int cur) {
    in[cur] = ++idx;
    for (Edge edge: graph[cur]) {
        if (edge.nxt != par[cur]) {
            top[edge.nxt] = (edge.nxt == graph[cur][0].nxt ? top[cur] : edge.nxt);
            dfs2(edge.nxt);
            weight[in[edge.nxt]] = edge.w;
        }
    }
    out[cur] = idx;
}
ll init(int idx, int s, int e) {
    if (s == e) {
        return tree[idx] = weight[s];
    }
    int m = (s + e) >> 1;
    return tree[idx] = max(init(2 * idx, s, m), init(2 * idx + 1, m + 1, e));
}
int update(int idx, int s, int e, int l, int r, int v) {
    if (r < s || e < l)
        return tree[idx];
    
    if (s == e)
        return tree[idx] = v;
    
    int m = (s + e) >> 1;
    return tree[idx] = max(update(2 * idx, s, m, l, r, v), update(2 * idx + 1, m + 1, e, l, r, v));
}
int maximum(int idx, int s, int e, int l, int r) {
    if (r < s || e < l)
        return 0;
    
    if (l <= s && e <= r)
        return tree[idx];
    
    int m = (s + e) >> 1;
    return max(maximum(2 * idx, s, m, l, r), maximum(2 * idx + 1, m + 1, e, l, r));
}
int query(int a, int b) {
    int ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] > dep[top[b]])
            swap(a, b);
        
        ret = max(ret, maximum(1, 1, N, in[top[b]], in[b]));
        b = par[top[b]];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    
    ret = max(ret, maximum(1, 1, N, in[a] + 1, in[b]));
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for (int i = 1; i < N; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
        edges[i] = {u, v};
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    init(1, 1, N);
    
    cin >> Q;
    while (Q--) {
        int q, u, v;
        cin >> q >> u >> v;
        if (q == 1) {
            int lower = (dep[edges[u].fi] > dep[edges[u].se] ? edges[u].fi : edges[u].se);
            update(1, 1, N, in[lower], in[lower], v);
        } else
            cout << query(u, v) << '\n';
    }
}
