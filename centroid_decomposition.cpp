// BOJ 13514 트리와 쿼리 5

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct LongestCommonAncestor {
    int n, k;
    vector<int> depth;
    vector<vector<int>> sparse;

    LongestCommonAncestor(int _n) {
        n = _n;
        k = ceil(log2(n)) + 1;

        depth.resize(n + 1);
        sparse.resize(k);
        for (int i = 0; i < k; i++)
            sparse[i].resize(n + 1);
    }

    void init(vector<vector<int>> &graph) {
        dfs(1, 1, graph);

        for (int i = 0; i < k - 1; i++)
            for (int j = 1; j <= n; j++)
                sparse[i + 1][j] = sparse[i][sparse[i][j]];
    }

    void dfs(int cur, int d, vector<vector<int>> &graph) {
        depth[cur] = d;

        for (int nxt : graph[cur]) {
            if (!depth[nxt]) {
                sparse[0][nxt] = cur;
                dfs(nxt, d + 1, graph);
            }
        }
    }

    int get(int a, int b) {
        if (depth[a] > depth[b])
            swap(a, b);

        int d = depth[b] - depth[a];
        for (int j = 0; j < k; j++)
            if (d & (1 << j))
                b = sparse[j][b];

        if (a == b)
            return a;

        while (1) {
            for (int j = k - 1; j >= 0; j--) {
                if (sparse[j][a] != sparse[j][b]) {
                    a = sparse[j][a];
                    b = sparse[j][b];
                }
            }

            if (sparse[0][a] == sparse[0][b])
                return sparse[0][a];
        }
    }

    int get_dist(int a, int b) { return depth[a] + depth[b] - 2 * depth[get(a, b)]; }
};

struct CentroidDecomposition {
    vector<bool> used;
    vector<int> sub;
    vector<int> parent;
    vector<vector<int>> tree;

    CentroidDecomposition(int n) {
        used.resize(n + 1);
        sub.resize(n + 1);
        parent.resize(n + 1);
        tree.resize(n + 1);
    }

    void init(int cur, int prv, vector<vector<int>> &graph) {
        int m = get_size(cur, 0, graph);
        int x = get_centroid(cur, 0, m, graph);

        tree[prv].push_back(x);
        parent[x] = prv;
        used[x] = true;

        for (int nxt : graph[x])
            if (!used[nxt])
                init(nxt, x, graph);
    }

    int get_size(int cur, int prv, vector<vector<int>> &graph) {
        sub[cur] = 1;

        for (int nxt : graph[cur])
            if (!used[nxt] && nxt != prv)
                sub[cur] += get_size(nxt, cur, graph);

        return sub[cur];
    }

    int get_centroid(int cur, int prv, int m, vector<vector<int>> &graph) {
        for (int nxt : graph[cur])
            if (!used[nxt] && nxt != prv && sub[nxt] > m / 2)
                return get_centroid(nxt, cur, m, graph);

        return cur;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    LongestCommonAncestor lca(n);
    lca.init(graph);

    CentroidDecomposition cd(n);
    cd.init(1, 0, graph);

    vector<vector<int>> pre(n + 1);
    for (int x = 1; x <= n; x++) {
        int y = x;

        while (y) {
            pre[x].push_back(lca.get_dist(x, y));
            y = cd.parent[y];
        }
    }

    vector<multiset<int>> v(n + 1);
    vector<bool> color(n + 1);

    int q;
    cin >> q;

    while (q--) {
        int op, x;
        cin >> op >> x;

        if (op == 1) {
            color[x] = !color[x];
            int y = x;
            int idx = 0;

            while (y) {
                int d = pre[x][idx++];

                if (color[x])
                    v[y].insert(d);
                else
                    v[y].erase(v[y].find(d));

                y = cd.parent[y];
            }
        } else {
            int ans = INT_MAX;
            int y = x;
            int idx = 0;

            while (y) {
                if (v[y].sz)
                    ans = min(ans, pre[x][idx] + *v[y].begin());

                y = cd.parent[y];
                idx++;
            }

            cout << (ans == INT_MAX ? -1 : ans) << '\n';
        }
    }
}
